#include "ssCloneScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"
#include "ssSceneManager.h"
#include "ssAnimator.h"
#include "ssResources.h"
#include "ssTexture.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssPlayer.h"
#include "ssValThunderEffect.h"
#include "ssCloneAssault.h"
#include "ssAudioClip.h"
#include "ssAudioSource.h"

namespace ss
{
	CloneScript::CloneScript()
		: mSpeed(1.f)
		, mRushStage(2)
		, mRushAxisDist(0.01f)
		, mRushBackDist(0.8f)
		, mRushDistCol(3.2f)
		, mRushDistRow(4.6f)
		, mRushSpeed(4.5f)  
		, mBackdistance(0.f)
	{
	}
	CloneScript::~CloneScript()
	{
	}
	void CloneScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
		mCollider = GetOwner()->GetComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Projectile);
		mTransform = GetOwner()->GetComponent<Transform>();
		mPos = mTransform->GetPosition();

		GameObject* audioSpeaker = new GameObject();
		mAs = audioSpeaker->AddComponent<AudioSource>();

		mAs->SetClip(Resources::Load<AudioClip>(L"CloneMakeSnd", L"..\\Resources\\Sound\\Valkyrie\\CloneMade.wav"));
		mAs->Play();
	}

	void CloneScript::Update()
	{
		mPlayerPos = PlayerScript::GetPlayerPos();
		mPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		
		LightningAssault();
	}


	void CloneScript::LightningAssault()
	{
		if (mRushStage == 0) //플레이어와 오/열 맞추기 전 방향 정하기
		{
			
		}
		else if (mRushStage == 1) // 플레이어와 오/열 맞추기
		{
			
		}
		else if (mRushStage == 2 && mStart) //러쉬전 뒤로 잠깐 빼기
		{
			if (!mMakeSndOnce)
			{
				mAs->SetClip(Resources::Find<AudioClip>(L"CloneMakeSnd"));
				mAs->Play();
				mMakeSndOnce = true;
			}
			float distance;
			if(mDir == e4Direction::Up)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushBackDist)
					mPos.y -= 2.f * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDir == e4Direction::Down)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushBackDist)
					mPos.y += 2.f * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDir == e4Direction::Right)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushBackDist)
					mPos.x -= 2.f * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}
			else if (mDir == e4Direction::Left)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushBackDist)
					mPos.x += 2.f * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}
			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance >= mRushBackDist)
			{
				mMakeSndOnce = false;
				mRushStage = 3;
				mRushBeforePos = mPos;
			}
		}
		else if (mRushStage == 3) //썬더이펙트 만들기
		{
			if (mDir == e4Direction::Up)
			{
				mAnimator->PlayAnimation(L"ValkAtkUp", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetClone(mClone);
						mThunderEffect->SetUp();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
						mRushStage = 4;
					}
				}

			}
			else if (mDir == e4Direction::Down)
			{
				mAnimator->PlayAnimation(L"ValkAtkDown", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetClone(mClone);
						mThunderEffect->SetDown();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
						mRushStage = 4;
					}
				}

			}
			else if (mDir == e4Direction::Right)
			{
				mAnimator->PlayAnimation(L"ValkAtkRight", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetClone(mClone);
						mThunderEffect->SetRight();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
						mRushStage = 4;
					}
				}
			}
			else if (mDir == e4Direction::Left)
			{
				mAnimator->PlayAnimation(L"ValkAtkLeft", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetClone(mClone);
						mThunderEffect->SetLeft();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
						mRushStage = 4;
					}
				}

			}

		}
		else if (mRushStage == 4) //돌진
		{
			if (!mAssaultSndOnce)
			{
				mAs->SetClip(Resources::Find<AudioClip>(L"AssaultSnd"));
				mAs->Play();
				mAssaultSndOnce = true;
			}

			float distance;
			if (mDir == e4Direction::Up)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushDistCol)
					mPos.y += mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDir == e4Direction::Down)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushDistCol)
					mPos.y -= mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDir == e4Direction::Right)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushDistRow)
					mPos.x += mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}
			else if (mDir == e4Direction::Left)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushDistRow)
					mPos.x -= mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}

			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance >= mRushDistCol
				&& (mDir == e4Direction::Up
					|| mDir == e4Direction::Down))
			{
				mRushStage++;
				mEffectCount = 0;
				mThunderEffect->SetDead();
				mThunderEffect = nullptr;
				mAssaultSndOnce = false;
			}
			else if (distance >= mRushDistRow
				&& (mDir == e4Direction::Right || mDir == e4Direction::Left))
			{
				mRushStage++;
				mEffectCount = 0;
				mThunderEffect->SetDead();
				mThunderEffect = nullptr;
				mAssaultSndOnce = false;
			}
		}
		else if (mRushStage == 5)
		{
			GetOwner()->SetState(GameObject::eState::Dead);
		}
		
	}
	

	void CloneScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			dynamic_cast<Player*>(other->GetOwner())->GetScript()->ChangeHp(-300.f);
		}
		else if (other->GetCollideType() == eCollideType::Player)
		{
			dynamic_cast<Player*>(other->GetOwner())->GetScript()->ChangeHp(-550.f);
		}
	}
	void CloneScript::OnCollisionStay(Collider2D* other)
	{

	}
	void CloneScript::OnCollisionExit(Collider2D* other)
	{
	}
}