#include "ssValkyrieScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"
#include "ssSceneManager.h"
#include < time.h >
#include "ssAnimator.h"
#include "ssResources.h"
#include "ssTexture.h"
#include "ssBossHpFill.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssValEffector.h"
#include "ssValThunderEffect.h"
#include "ssValkyrie.h"
#include "ssPlayer.h"
#include "ssBigLightning.h"
#include "ssCloneAssault.h"
#include "ssCloneScript.h"
#include "ssLightBall.h"
#include "ssSpearRain.h"
#include "ssSpearPiece.h"

namespace ss
{
	ValkyrieScript::ValkyrieScript()
		: mHp(20000.0f)
		, mSpeed(1.f)
		, mRushStage(0)
		, mRushAxisDist(0.01f)
		, mRushBackDist(0.8f)
		, mRushDistCol(3.2f)
		, mRushDistRow(4.1f)
		, mRushSpeed(4.5f)
		, mEffectCount(0)
		, mBigStage(0)
		, mBallStage(0)
		, mRainStage(0)
		, mInterval(0.f)
		, mPieceCount(0)
		, mPatternNum(0)
		, mPatternTime(0.f)
		, mDeadStage(0)
		, mAlpha(1.f)
		, mTransformAniStage(0)
		, mCenterPoint(-0.136f, 6.37f, 1.f)
	{
	}
	ValkyrieScript::~ValkyrieScript()
	{
	}
	void ValkyrieScript::Initialize()
	{

		mAnimator = GetOwner()->GetComponent<Animator>();
		mCollider = GetOwner()->GetComponent<Collider2D>();
		mTransform = GetOwner()->GetComponent<Transform>();

		mPos = mTransform->GetPosition();

		mState = eState::Sleep;
		mDirState = eDirState::Down;
	}

	void ValkyrieScript::Update()
	{
		mPlayerPos = PlayerScript::GetPlayerPos();
		mPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		DamageCheck();
		mBossHpFill->ChangeHP(mHp);

		if (!mAwake && mValk->GetAwake())
		{
			mAwake = true;
			mState = eState::Transform;
		}

		if (mHp <= 0)
			mState = eState::Dead;

		

		switch (mState)
		{
		case ss::ValkyrieScript::eState::Dead:
			Dead();
			break;
		case ss::ValkyrieScript::eState::Positioning:
			Positioning();
			break;
		case ss::ValkyrieScript::eState::Sleep:
			break;
		case ss::ValkyrieScript::eState::Transform:
			PlayTransform();
			break;
		case ss::ValkyrieScript::eState::Chase:
			Chase();
			break;
		case ss::ValkyrieScript::eState::LightningRush:
			LightningRush();
			break;
		case ss::ValkyrieScript::eState::LightningAssault:
			LightningAssault();
			break;
		case ss::ValkyrieScript::eState::CloneAssault:
			CloneAssaultCast();
			break;
		case ss::ValkyrieScript::eState::BigLightning:
			BigLightningCast();
			break;
		case ss::ValkyrieScript::eState::ThrowRightBall:
			ThrowLightBall();
			break;
		case ss::ValkyrieScript::eState::SpearRainCast:
			SpearRainCast();
			break;
		default:
			break;
		}
		


		/*if (Input::GetKey(eKeyCode::P))
		{
			mState = eState::Dead;
		}*/
		
	}

	void ValkyrieScript::Render()
	{
		if (mCloneOnce)//클론 동기화
		{
			mClone->SetStart();
			mRushStage = 3;
		}
	}

	void ValkyrieScript::Positioning()
	{
		CalDir(mCenterPoint);
		WalkAni();

		
		if (mPos.x < mCenterPoint.x)
			mPos.x += mSpeed * Time::DeltaTime();
		else
			mPos.x -= mSpeed * Time::DeltaTime();

		if (mPos.y < mCenterPoint.y)
			mPos.y += mSpeed * Time::DeltaTime();
		else
			mPos.y -= mSpeed * Time::DeltaTime();

		GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

		float Distance = math::GetDistance(mPos, mCenterPoint);

		if (Distance < 1.7f)
			mState = eState::Chase;
	}

	void ValkyrieScript::Dead()
	{
		if (mDeadStage == 0)
		{
			mValk->SetDead();
			mDirState = eDirState::Down;
			WalkAni();
			mEffector->PlayDeathEffect();

			if (mEffector->GetDeathAniPlayed())
				mDeadStage++;
		}
		else if (mDeadStage == 1)
		{
			mAlpha -= 1.f * Time::DeltaTime();

			mValk->SetAhlphaMater(mAlpha);

			if (mAlpha < 0)
				mDeadStage++;
		}
		else if (mDeadStage == 2)
		{
			GetOwner()->SetState(GameObject::eState::Dead);
		}
		
	}

	void ValkyrieScript::Chase()
	{
		if (math::GetDistance(mCenterPoint, mPos) > 2.6f)
		{
			mState = eState::Positioning;
			return;
		}

		CalDir(mPlayerPos);
		WalkAni();

		float Distance = math::GetDistance(mPos, mPlayerPos);

		if (Distance > 1.3f)
		{
			if (mPos.x < mPlayerPos.x)
				mPos.x += mSpeed * Time::DeltaTime();
			else
				mPos.x -= mSpeed * Time::DeltaTime();

			if (mPos.y < mPlayerPos.y)
				mPos.y += mSpeed * Time::DeltaTime();
			else
				mPos.y -= mSpeed * Time::DeltaTime();
		}
		else if (Distance < 0.7f)
		{

			if (mPos.x < mPlayerPos.x)
				mPos.x -= mSpeed * Time::DeltaTime();
			else
				mPos.x += mSpeed * Time::DeltaTime();

			if (mPos.y < mPlayerPos.y)
				mPos.y -= mSpeed * Time::DeltaTime();
			else
				mPos.y += mSpeed * Time::DeltaTime();
		}
		
		GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

		if (mHp > 14000.f)
			Pattern();
		else
		{
			Pattern2();
		}

	}

	void ValkyrieScript::WalkAni()
	{
		switch (mDirState)
		{
		case ss::ValkyrieScript::eDirState::Up:
			mAnimator->PlayAnimation(L"ValkWalkUp", true);
			break;
		case ss::ValkyrieScript::eDirState::UpRight:
			mAnimator->PlayAnimation(L"ValkWalkUp", true);
			break;
		case ss::ValkyrieScript::eDirState::UpLeft:
			mAnimator->PlayAnimation(L"ValkWalkUp", true);
			break;
		case ss::ValkyrieScript::eDirState::Down:
			mAnimator->PlayAnimation(L"ValkWalkDown", true);
			break;
		case ss::ValkyrieScript::eDirState::DownRight:
			mAnimator->PlayAnimation(L"ValkWalkDown", true);
			break;
		case ss::ValkyrieScript::eDirState::DownLeft:
			mAnimator->PlayAnimation(L"ValkWalkDown", true);
			break;
		case ss::ValkyrieScript::eDirState::Right:
			mAnimator->PlayAnimation(L"ValkWalkRight", true);
			break;
		case ss::ValkyrieScript::eDirState::Left:
			mAnimator->PlayAnimation(L"ValkWalkLeft", true);
			break;
		default:
			break;
		}
	}

	void ValkyrieScript::PlayTransform()
	{
		if (mTransformAniStage == 0)
		{
			mAnimator->PlayAnimation(L"ValkTurn", false);
			if (mAnimator->GetActiveAnimation()->IsComplete())
				mTransformAniStage = 1;
		}
		else if (mTransformAniStage == 1)
		{
			mAnimator->PlayAnimation(L"ValkAfterTurn", false);
			if (mAnimator->GetActiveAnimation()->IsComplete())
				mTransformAniStage = 2;
		}
		else if (mTransformAniStage == 2)
		{
			mAnimator->PlayAnimation(L"ValkTransform", false);
			if (mAnimator->GetActiveAnimation()->IsComplete())
				mTransformAniStage = 3;
		}
		else if (mTransformAniStage == 3)
		{
			mValk->SetEventComplete(true);
			mState = eState::Chase;
		}
	}

	void ValkyrieScript::LightningRush()
	{
		if (mRushStage == 0)
		{
			CalDir(mPlayerPos);
			float xDiff = abs(mPos.x - mPlayerPos.x);
			float yDiff = abs(mPos.y - mPlayerPos.y);

			switch (mDirState)
			{
			case ss::ValkyrieScript::eDirState::Up:
				break;
			case ss::ValkyrieScript::eDirState::UpRight:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Up;
				else
					mDirState = eDirState::Right;
				break;
			}
			case ss::ValkyrieScript::eDirState::UpLeft:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Up;
				else
					mDirState = eDirState::Left;
				break;
			}
			case ss::ValkyrieScript::eDirState::Down:
				break;
			case ss::ValkyrieScript::eDirState::DownRight:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Down;
				else
					mDirState = eDirState::Right;
				break;
			}
			case ss::ValkyrieScript::eDirState::DownLeft:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Down;
				else
					mDirState = eDirState::Left;
				break;
			}
			case ss::ValkyrieScript::eDirState::Right:
				break;
			case ss::ValkyrieScript::eDirState::Left:
				break;
			default:
				break;
			}

			WalkAni();
			mRushStage = 1;
		}
		else if (mRushStage == 1)
		{
			float distance;
			if (mDirState == eDirState::Up
				|| mDirState == eDirState::UpRight
				|| mDirState == eDirState::UpLeft)
			{
				distance = abs(mPos.x - mPlayerPos.x);
				if (mPos.x < mPlayerPos.x && distance > mRushAxisDist)
					mPos.x += 2.5f * Time::DeltaTime();
				else if(mPos.x > mPlayerPos.x && distance > mRushAxisDist)
					mPos.x -= 2.5f * Time::DeltaTime();
			}
			else if (mDirState == eDirState::Down
				|| mDirState == eDirState::DownRight
				|| mDirState == eDirState::DownLeft)
			{
				distance = abs(mPos.x - mPlayerPos.x);
				if (mPos.x < mPlayerPos.x && distance > mRushAxisDist)
					mPos.x += 2.5f * Time::DeltaTime();
				else if (mPos.x > mPlayerPos.x && distance > mRushAxisDist)
					mPos.x -= 2.5f * Time::DeltaTime();
			}
			else if (mDirState == eDirState::Right)
			{
				distance = abs(mPos.y - mPlayerPos.y);
				if (mPos.y < mPlayerPos.y && distance > mRushAxisDist)
					mPos.y += 2.5f * Time::DeltaTime();
				else if (mPos.y > mPlayerPos.y && distance > mRushAxisDist)
					mPos.y -= 2.5f * Time::DeltaTime();
			}
			else if (mDirState == eDirState::Left)
			{
				distance = abs(mPos.y - mPlayerPos.y);
				if (mPos.y < mPlayerPos.y && distance > mRushAxisDist)
					mPos.y += 2.5f * Time::DeltaTime();
				else if (mPos.y > mPlayerPos.y && distance > mRushAxisDist)
					mPos.y -= 2.5f * Time::DeltaTime();
			}

			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance <= mRushAxisDist)
			{
				mRushStage = 2;
				mRushBeforePos = mPos;
			}
		}
		else if (mRushStage == 2)
		{
			float distance;
			if (mDirState == eDirState::Up
				|| mDirState == eDirState::UpRight
				|| mDirState == eDirState::UpLeft)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if(distance < mRushBackDist)
					mPos.y -= 2.f * Time::DeltaTime();
			}
			else if (mDirState == eDirState::Down
				|| mDirState == eDirState::DownRight
				|| mDirState == eDirState::DownLeft)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushBackDist)
					mPos.y += 2.f * Time::DeltaTime();
			}
			else if (mDirState == eDirState::Right)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushBackDist)
					mPos.x -= 2.f * Time::DeltaTime();
			}
			else if (mDirState == eDirState::Left)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushBackDist)
					mPos.x += 2.f * Time::DeltaTime();
			}
			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance >= mRushBackDist)
			{
				mRushStage = 3;
				mRushBeforePos = mPos;
			}
		}
		else if (mRushStage == 3)
		{
			mColState = eColideState::Rush;
			ChangeColSetting();
			float distance;
			if (mDirState == eDirState::Up
				|| mDirState == eDirState::UpRight
				|| mDirState == eDirState::UpLeft)
			{
				mAnimator->PlayAnimation(L"ValkAtkUp", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
					mEffector->PlayNormalRushEffect(e4Direction::Up);

				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushDistCol)
					mPos.y += mRushSpeed * Time::DeltaTime();
			}
			else if (mDirState == eDirState::Down
				|| mDirState == eDirState::DownRight
				|| mDirState == eDirState::DownLeft)
			{
				mAnimator->PlayAnimation(L"ValkAtkDown", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
					mEffector->PlayNormalRushEffect(e4Direction::Down);

				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushDistCol)
					mPos.y -= mRushSpeed * Time::DeltaTime();
			}
			else if (mDirState == eDirState::Right)
			{
				mAnimator->PlayAnimation(L"ValkAtkRight", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
					mEffector->PlayNormalRushEffect(e4Direction::Right);

				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushDistRow)
					mPos.x += mRushSpeed * Time::DeltaTime();
			}
			else if (mDirState == eDirState::Left)
			{
				mAnimator->PlayAnimation(L"ValkAtkLeft", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
					mEffector->PlayNormalRushEffect(e4Direction::Left);

				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushDistRow)
					mPos.x -= mRushSpeed * Time::DeltaTime();
			}

			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance >= mRushDistCol 
				&& (mDirState == eDirState::Up
					|| mDirState == eDirState::UpRight
					|| mDirState == eDirState::UpLeft
					|| mDirState == eDirState::Down
					|| mDirState == eDirState::DownRight
					|| mDirState == eDirState::DownLeft))
			{
				mRushStage = 0;
				mColState = eColideState::Normal;
				ChangeColSetting();
				mState = eState::Chase;
			}
			else if (distance >= mRushDistRow
				&& (mDirState == eDirState::Right || mDirState == eDirState::Left))
			{
				mRushStage = 0;
				mColState = eColideState::Normal;
				ChangeColSetting();
				mState = eState::Chase;
			}

		}

	}

	void ValkyrieScript::LightningAssault()
	{
		if (mRushStage == 0) //플레이어와 오/열 맞추기 전 방향 정하기
		{
			CalDir(mPlayerPos);
			float xDiff = abs(mPos.x - mPlayerPos.x);
			float yDiff = abs(mPos.y - mPlayerPos.y);

			switch (mDirState)
			{
			case ss::ValkyrieScript::eDirState::Up:
				break;
			case ss::ValkyrieScript::eDirState::UpRight:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Up;
				else
					mDirState = eDirState::Right;
				break;
			}
			case ss::ValkyrieScript::eDirState::UpLeft:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Up;
				else
					mDirState = eDirState::Left;
				break;
			}
			case ss::ValkyrieScript::eDirState::Down:
				break;
			case ss::ValkyrieScript::eDirState::DownRight:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Down;
				else
					mDirState = eDirState::Right;
				break;
			}
			case ss::ValkyrieScript::eDirState::DownLeft:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Down;
				else
					mDirState = eDirState::Left;
				break;
			}
			case ss::ValkyrieScript::eDirState::Right:
				break;
			case ss::ValkyrieScript::eDirState::Left:
				break;
			default:
				break;
			}

			WalkAni();
			mRushStage = 1;
		}
		else if (mRushStage == 1) // 플레이어와 오/열 맞추기
		{
			float distance;
			if (mDirState == eDirState::Up
				|| mDirState == eDirState::UpRight
				|| mDirState == eDirState::UpLeft)
			{
				distance = abs(mPos.x - mPlayerPos.x);

				if (mPos.x < mPlayerPos.x && distance > mRushAxisDist)
					mPos.x += 2.5f * Time::DeltaTime();
				else if (mPos.x > mPlayerPos.x && distance > mRushAxisDist)
					mPos.x -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.x - mPlayerPos.x);
			}
			else if (mDirState == eDirState::Down
				|| mDirState == eDirState::DownRight
				|| mDirState == eDirState::DownLeft)
			{
				distance = abs(mPos.x - mPlayerPos.x);

				if (mPos.x < mPlayerPos.x && distance > mRushAxisDist)
					mPos.x += 2.5f * Time::DeltaTime();
				else if (mPos.x > mPlayerPos.x && distance > mRushAxisDist)
					mPos.x -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.x - mPlayerPos.x);
			}
			else if (mDirState == eDirState::Right)
			{
				distance = abs(mPos.y - mPlayerPos.y);

				if (mPos.y < mPlayerPos.y && distance > mRushAxisDist)
					mPos.y += 2.5f * Time::DeltaTime();
				else if (mPos.y > mPlayerPos.y && distance > mRushAxisDist)
					mPos.y -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.y - mPlayerPos.y);
			}
			else if (mDirState == eDirState::Left)
			{
				distance = abs(mPos.y - mPlayerPos.y);

				if (mPos.y < mPlayerPos.y && distance > mRushAxisDist)
					mPos.y += 2.5f * Time::DeltaTime();
				else if (mPos.y > mPlayerPos.y && distance > mRushAxisDist)
					mPos.y -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.y - mPlayerPos.y);
			}

			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance <= mRushAxisDist)
			{
				mRushStage = 2;
				mRushBeforePos = mPos;
			}
		}
		else if (mRushStage == 2) //러쉬전 뒤로 잠깐 빼기
		{
			float distance;
			if (mDirState == eDirState::Up
				|| mDirState == eDirState::UpRight
				|| mDirState == eDirState::UpLeft)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushBackDist)
					mPos.y -= 2.f * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDirState == eDirState::Down
				|| mDirState == eDirState::DownRight
				|| mDirState == eDirState::DownLeft)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushBackDist)
					mPos.y += 2.f * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDirState == eDirState::Right)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushBackDist)
					mPos.x -= 2.f * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}
			else if (mDirState == eDirState::Left)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushBackDist)
					mPos.x += 2.f * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}
			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance >= mRushBackDist)
			{
				mRushStage = 3;
				mRushBeforePos = mPos;
			}
		}
		else if (mRushStage == 3) //썬더이펙트 만들기
		{
			mColState = eColideState::Assault;
			ChangeColSetting();
			
			if (mDirState == eDirState::Up)
			{
				mAnimator->PlayAnimation(L"ValkAtkUp", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetValkyrie(mValk);
						mThunderEffect->SetUp();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
						mRushStage = 4;
					}
				}
				
			}
			else if (mDirState == eDirState::Down)
			{
				mAnimator->PlayAnimation(L"ValkAtkDown", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetValkyrie(mValk);
						mThunderEffect->SetDown();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
						mRushStage = 4;
					}
				}
				
			}
			else if (mDirState == eDirState::Right)
			{
				mAnimator->PlayAnimation(L"ValkAtkRight", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetValkyrie(mValk);
						mThunderEffect->SetRight();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
						mRushStage = 4;
					}
				}
			}
			else if (mDirState == eDirState::Left)
			{
				mAnimator->PlayAnimation(L"ValkAtkLeft", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetValkyrie(mValk);
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
			float distance;
			if (mDirState == eDirState::Up)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushDistCol)
					mPos.y += mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDirState == eDirState::Down)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushDistCol)
					mPos.y -= mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDirState == eDirState::Right)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushDistRow)
					mPos.x += mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}
			else if (mDirState == eDirState::Left)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushDistRow)
					mPos.x -= mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}

			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance >= mRushDistCol
				&& (mDirState == eDirState::Up
					|| mDirState == eDirState::Down))
			{
				mRushStage = 0;
				mEffectCount = 0;
				mThunderEffect->SetDead();
				mThunderEffect = nullptr;
				mColState = eColideState::Normal;
				ChangeColSetting();
				mState = eState::Chase;
			}
			else if (distance >= mRushDistRow
				&& (mDirState == eDirState::Right || mDirState == eDirState::Left))
			{
				mRushStage = 0;
				mEffectCount = 0;
				mThunderEffect->SetDead();
				mThunderEffect = nullptr;
				mColState = eColideState::Normal;
				ChangeColSetting();
				mState = eState::Chase;
			}
		}
	}

	void ValkyrieScript::BigLightningCast()
	{
		if (mBigStage == 0)
		{
			CalDir(mPlayerPos);
			WalkAni();

			Vector3 CastPos = Vector3(mPlayerPos.x, mPlayerPos.y + 1.f, mPlayerPos.z);
			float Distance = math::GetDistance(mPos, CastPos);

			if (Distance > 0.05f)
			{
				if (mPos.x < CastPos.x)
					mPos.x += 4.f * Time::DeltaTime();
				else
					mPos.x -= 4.f * Time::DeltaTime();

				if (mPos.y < CastPos.y)
					mPos.y += 4.f * Time::DeltaTime();
				else
					mPos.y -= 4.f * Time::DeltaTime();

				mTransform->SetPosition(mPos);
			}
			else
				mBigStage = 1;

		}
		else if (mBigStage == 1)
		{
			mAnimator->PlayAnimation(L"ValkCast", true);
			mPlayerPos = PlayerScript::GetPlayerPos();
			mBig = new BigLightning();
			Vector3 pos = mPlayerPos;
			pos.z += 0.1f;
			mBig->SetPosition(pos);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, mBig);

			mBigStage++;
		}
		else if (mBigStage == 2)
		{
			if (mEffector->PlayChargeNewAndMiddle()
				&& mBig->GetStage() >= 1)
				mBigStage++;
		}
		else if (mBigStage == 3)
		{
			if (mEffector->PlayChargeEffectEnd())
			{
				mBigStage = 0;
				mState = eState::Chase;
			}
		}
		
	}

	void ValkyrieScript::CloneAssaultCast()
	{
		if (mRushStage == 0) //플레이어와 오/열 맞추기 전 방향 정하기
		{
			CalDir(mPlayerPos);
			float xDiff = abs(mPos.x - mPlayerPos.x);
			float yDiff = abs(mPos.y - mPlayerPos.y);

			switch (mDirState)
			{
			case ss::ValkyrieScript::eDirState::Up:
				break;
			case ss::ValkyrieScript::eDirState::UpRight:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Up;
				else
					mDirState = eDirState::Right;
				break;
			}
			case ss::ValkyrieScript::eDirState::UpLeft:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Up;
				else
					mDirState = eDirState::Left;
				break;
			}
			case ss::ValkyrieScript::eDirState::Down:
				break;
			case ss::ValkyrieScript::eDirState::DownRight:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Down;
				else
					mDirState = eDirState::Right;
				break;
			}
			case ss::ValkyrieScript::eDirState::DownLeft:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Down;
				else
					mDirState = eDirState::Left;
				break;
			}
			case ss::ValkyrieScript::eDirState::Right:
				break;
			case ss::ValkyrieScript::eDirState::Left:
				break;
			default:
				break;
			}

			WalkAni();
			mRushStage = 1;
		}
		else if (mRushStage == 1) // 플레이어와 오/열 맞추기
		{
			float distance;
			if (mDirState == eDirState::Up
				|| mDirState == eDirState::UpRight
				|| mDirState == eDirState::UpLeft)
			{
				distance = abs(mPos.x - mPlayerPos.x);

				if (mPos.x < mPlayerPos.x && distance > mRushAxisDist)
					mPos.x += 2.5f * Time::DeltaTime();
				else if (mPos.x > mPlayerPos.x && distance > mRushAxisDist)
					mPos.x -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.x - mPlayerPos.x);
			}
			else if (mDirState == eDirState::Down
				|| mDirState == eDirState::DownRight
				|| mDirState == eDirState::DownLeft)
			{
				distance = abs(mPos.x - mPlayerPos.x);

				if (mPos.x < mPlayerPos.x && distance > mRushAxisDist)
					mPos.x += 2.5f * Time::DeltaTime();
				else if (mPos.x > mPlayerPos.x && distance > mRushAxisDist)
					mPos.x -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.x - mPlayerPos.x);
			}
			else if (mDirState == eDirState::Right)
			{
				distance = abs(mPos.y - mPlayerPos.y);

				if (mPos.y < mPlayerPos.y && distance > mRushAxisDist)
					mPos.y += 2.5f * Time::DeltaTime();
				else if (mPos.y > mPlayerPos.y && distance > mRushAxisDist)
					mPos.y -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.y - mPlayerPos.y);
			}
			else if (mDirState == eDirState::Left)
			{
				distance = abs(mPos.y - mPlayerPos.y);

				if (mPos.y < mPlayerPos.y && distance > mRushAxisDist)
					mPos.y += 2.5f * Time::DeltaTime();
				else if (mPos.y > mPlayerPos.y && distance > mRushAxisDist)
					mPos.y -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.y - mPlayerPos.y);
			}

			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance <= mRushAxisDist)
			{
				mRushStage++;
				mRushBeforePos = mPos;
			}
		}
		else if (mRushStage == 2) // 클론 생성
		{
			if (mDirState == eDirState::Up)
			{
				if (!mCloneOnce)
				{
					mClone = new CloneAssault(e4Direction::Down);
					Vector3 clonePos = GetOwner()->GetComponent<Transform>()->GetPosition();
					clonePos.y += abs(PlayerScript::GetPlayerPos().y - clonePos.y) * 2.f;
					mClone->GetComponent<Transform>()->SetPosition(clonePos);
					mClone->GetComponent<CloneScript>()->SetBeforePos(clonePos);
					SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mClone);
					mCloneOnce = true;
				}
			}
			else if (mDirState == eDirState::Down)
			{
				if (!mCloneOnce)
				{
					mClone = new CloneAssault(e4Direction::Up);
					Vector3 clonePos = GetOwner()->GetComponent<Transform>()->GetPosition();
					clonePos.y -= abs(PlayerScript::GetPlayerPos().y - clonePos.y) * 2.f;
					mClone->GetComponent<Transform>()->SetPosition(clonePos);
					mClone->GetComponent<CloneScript>()->SetBeforePos(clonePos);
					SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mClone);
					mCloneOnce = true;
				}
			}
			else if (mDirState == eDirState::Right)
			{
				if (!mCloneOnce)
				{
					mClone = new CloneAssault(e4Direction::Left);
					Vector3 clonePos = GetOwner()->GetComponent<Transform>()->GetPosition();
					clonePos.x += abs(PlayerScript::GetPlayerPos().x - clonePos.x) * 2.f;
					mClone->GetComponent<Transform>()->SetPosition(clonePos);
					mClone->GetComponent<CloneScript>()->SetBeforePos(clonePos);
					SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mClone);
					mCloneOnce = true;
				}
			}
			else if (mDirState == eDirState::Left)
			{
				if (!mCloneOnce)
				{
					mClone = new CloneAssault(e4Direction::Right);
					Vector3 clonePos = GetOwner()->GetComponent<Transform>()->GetPosition();
					clonePos.x -= abs(PlayerScript::GetPlayerPos().x - clonePos.x) * 2.f;
					mClone->GetComponent<Transform>()->SetPosition(clonePos);
					mClone->GetComponent<CloneScript>()->SetBeforePos(clonePos);
					SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mClone);
					mCloneOnce = true;
				}
			}
		}
		else if (mRushStage == 3) //러쉬전 뒤로 잠깐 빼기
		{
			mCloneOnce = false;
			float distance;
			if (mDirState == eDirState::Up
				|| mDirState == eDirState::UpRight
				|| mDirState == eDirState::UpLeft)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushBackDist)
					mPos.y -= 2.f * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDirState == eDirState::Down
				|| mDirState == eDirState::DownRight
				|| mDirState == eDirState::DownLeft)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushBackDist)
					mPos.y += 2.f * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDirState == eDirState::Right)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushBackDist)
					mPos.x -= 2.f * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}
			else if (mDirState == eDirState::Left)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushBackDist)
					mPos.x += 2.f * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}
			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance >= mRushBackDist)
			{
				mRushStage++;
				mRushBeforePos = mPos;
			}
		}
		else if (mRushStage == 4) //썬더이펙트 만들기
		{
			mColState = eColideState::Assault;
			ChangeColSetting();

			if (mDirState == eDirState::Up)
			{
				mAnimator->PlayAnimation(L"ValkAtkUp", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetValkyrie(mValk);
						mThunderEffect->SetUp();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
						mRushStage++;
					}
				}

			}
			else if (mDirState == eDirState::Down)
			{
				mAnimator->PlayAnimation(L"ValkAtkDown", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetValkyrie(mValk);
						mThunderEffect->SetDown();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
						mRushStage++;
					}
				}

			}
			else if (mDirState == eDirState::Right)
			{
				mAnimator->PlayAnimation(L"ValkAtkRight", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetValkyrie(mValk);
						mThunderEffect->SetRight();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
						mRushStage++;
					}
				}
			}
			else if (mDirState == eDirState::Left)
			{
				mAnimator->PlayAnimation(L"ValkAtkLeft", false);
				if (mAnimator->GetActiveAnimation()->IsComplete())
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetValkyrie(mValk);
						mThunderEffect->SetLeft();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
						mRushStage++;
					}
				}

			}

		}
		else if (mRushStage == 5) //돌진
		{
			float distance;
			if (mDirState == eDirState::Up)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushDistCol)
					mPos.y += mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDirState == eDirState::Down)
			{
				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushDistCol)
					mPos.y -= mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.y - mRushBeforePos.y);
			}
			else if (mDirState == eDirState::Right)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushDistRow)
					mPos.x += mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}
			else if (mDirState == eDirState::Left)
			{
				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushDistRow)
					mPos.x -= mRushSpeed * Time::DeltaTime();

				distance = abs(mPos.x - mRushBeforePos.x);
			}

			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance >= mRushDistCol
				&& (mDirState == eDirState::Up
					|| mDirState == eDirState::Down))
			{
				mRushStage = 0;
				mEffectCount = 0;
				mThunderEffect->SetDead();
				mThunderEffect = nullptr;
				mColState = eColideState::Normal;
				ChangeColSetting();
				mState = eState::Chase;
			}
			else if (distance >= mRushDistRow
				&& (mDirState == eDirState::Right || mDirState == eDirState::Left))
			{
				mRushStage = 0;
				mEffectCount = 0;
				mThunderEffect->SetDead();
				mThunderEffect = nullptr;
				mColState = eColideState::Normal;
				ChangeColSetting();
				mState = eState::Chase;
			}
		}

	}

	void ValkyrieScript::ThrowLightBall()
	{
		CalDir(mPlayerPos);
		
		if (mBallStage == 0) //방향정하기
		{
			CalDir(mPlayerPos);
			float xDiff = abs(mPos.x - mPlayerPos.x);
			float yDiff = abs(mPos.y - mPlayerPos.y);

			switch (mDirState)
			{
			case ss::ValkyrieScript::eDirState::Up:
				break;
			case ss::ValkyrieScript::eDirState::UpRight:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Up;
				else
					mDirState = eDirState::Right;
				break;
			}
			case ss::ValkyrieScript::eDirState::UpLeft:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Up;
				else
					mDirState = eDirState::Left;
				break;
			}
			case ss::ValkyrieScript::eDirState::Down:
				break;
			case ss::ValkyrieScript::eDirState::DownRight:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Down;
				else
					mDirState = eDirState::Right;
				break;
			}
			case ss::ValkyrieScript::eDirState::DownLeft:
			{
				if (xDiff <= yDiff)
					mDirState = eDirState::Down;
				else
					mDirState = eDirState::Left;
				break;
			}
			case ss::ValkyrieScript::eDirState::Right:
				break;
			case ss::ValkyrieScript::eDirState::Left:
				break;
			default:
				break;
			}

			WalkAni();
			mBallStage = 1;
		}
		else if (mBallStage == 1) //오/열 맞추기
		{
			float distance;
			if (mDirState == eDirState::Up
				|| mDirState == eDirState::UpRight
				|| mDirState == eDirState::UpLeft)
			{
				distance = abs(mPos.x - mPlayerPos.x);

				if (mPos.x < mPlayerPos.x && distance > mRushAxisDist)
					mPos.x += 2.5f * Time::DeltaTime();
				else if (mPos.x > mPlayerPos.x && distance > mRushAxisDist)
					mPos.x -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.x - mPlayerPos.x);
			}
			else if (mDirState == eDirState::Down
				|| mDirState == eDirState::DownRight
				|| mDirState == eDirState::DownLeft)
			{
				distance = abs(mPos.x - mPlayerPos.x);

				if (mPos.x < mPlayerPos.x && distance > mRushAxisDist)
					mPos.x += 2.5f * Time::DeltaTime();
				else if (mPos.x > mPlayerPos.x && distance > mRushAxisDist)
					mPos.x -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.x - mPlayerPos.x);
			}
			else if (mDirState == eDirState::Right)
			{
				distance = abs(mPos.y - mPlayerPos.y);

				if (mPos.y < mPlayerPos.y && distance > mRushAxisDist)
					mPos.y += 2.5f * Time::DeltaTime();
				else if (mPos.y > mPlayerPos.y && distance > mRushAxisDist)
					mPos.y -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.y - mPlayerPos.y);
			}
			else if (mDirState == eDirState::Left)
			{
				distance = abs(mPos.y - mPlayerPos.y);

				if (mPos.y < mPlayerPos.y && distance > mRushAxisDist)
					mPos.y += 2.5f * Time::DeltaTime();
				else if (mPos.y > mPlayerPos.y && distance > mRushAxisDist)
					mPos.y -= 2.5f * Time::DeltaTime();

				distance = abs(mPos.y - mPlayerPos.y);
			}

			GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

			if (distance <= mRushAxisDist)
			{
				mBallStage = 2;
				mRushBeforePos = mPos;
			}
		}
		else if (mBallStage == 2)
		{
			switch (mDirState)
			{
			case ss::ValkyrieScript::eDirState::Up:
				mAnimator->PlayAnimation(L"ValkThrowUp", false);
				break;
			case ss::ValkyrieScript::eDirState::UpRight:
				break;
			case ss::ValkyrieScript::eDirState::UpLeft:
				break;
			case ss::ValkyrieScript::eDirState::Down:
				mAnimator->PlayAnimation(L"ValkThrowDown", false);
				break;
			case ss::ValkyrieScript::eDirState::DownRight:
				break;
			case ss::ValkyrieScript::eDirState::DownLeft:
				break;
			case ss::ValkyrieScript::eDirState::Right:
				mAnimator->PlayAnimation(L"ValkThrowRight", false);
				break;
			case ss::ValkyrieScript::eDirState::Left:
				mAnimator->PlayAnimation(L"ValkThrowLeft", false);
				break;
			default:
				break;
			}

			if (mAnimator->GetActiveAnimation()->IsComplete())
				mBallStage = 3;
		}
		else if (mBallStage == 3)
		{
			switch (mDirState)
			{
			case ss::ValkyrieScript::eDirState::Up:
			{
				LightBall* ball = new LightBall(e4Direction::Up);
				Vector3 pos = mPos;
				pos.y += 0.5f;
				ball->GetComponent<Transform>()->SetPosition(pos);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, ball);
			}
				break;
			case ss::ValkyrieScript::eDirState::UpRight:
				break;
			case ss::ValkyrieScript::eDirState::UpLeft:
				break;
			case ss::ValkyrieScript::eDirState::Down:
			{
				LightBall* ball = new LightBall(e4Direction::Down);
				Vector3 pos = mPos;
				pos.y -= 0.5f;
				ball->GetComponent<Transform>()->SetPosition(pos);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, ball);
			}
				break;
			case ss::ValkyrieScript::eDirState::DownRight:
				break;
			case ss::ValkyrieScript::eDirState::DownLeft:
				break;
			case ss::ValkyrieScript::eDirState::Right:
			{
				LightBall* ball = new LightBall(e4Direction::Right);
				Vector3 pos = mPos;
				pos.x += 0.5f;
				ball->GetComponent<Transform>()->SetPosition(pos);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, ball);
			}
				break;
			case ss::ValkyrieScript::eDirState::Left:
			{
				LightBall* ball = new LightBall(e4Direction::Left);
				Vector3 pos = mPos;
				pos.x -= 0.5f;
				ball->GetComponent<Transform>()->SetPosition(pos);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, ball);
			}
				break;
			default:
				break;
			}

			mBallStage = 4;
		}
		else if (mBallStage == 4)
		{
			mBallStage = 0;
			mState = eState::Chase;
		}
	}

	void ValkyrieScript::SpearRainCast()
	{
		if (mRainStage == 1)
		{
			mRainTargetPos = mPlayerPos;
			mRainTargetPos.z += 0.01f;
			mRainStage++;
		}
		else if (mRainStage == 0)
		{
			CalDir(mPlayerPos);
			
			switch (mDirState)
			{
			case ss::ValkyrieScript::eDirState::Up:
				mAnimator->PlayAnimation(L"ValkThrowUpUp", false);
				break;
			case ss::ValkyrieScript::eDirState::UpRight:
				mAnimator->PlayAnimation(L"ValkThrowUpUp", false);
				break;
			case ss::ValkyrieScript::eDirState::UpLeft:
				mAnimator->PlayAnimation(L"ValkThrowUpUp", false);
				break;
			case ss::ValkyrieScript::eDirState::Down:
				mAnimator->PlayAnimation(L"ValkThrowUpDown", false);
				break;
			case ss::ValkyrieScript::eDirState::DownRight:
				mAnimator->PlayAnimation(L"ValkThrowUpDown", false);
				break;
			case ss::ValkyrieScript::eDirState::DownLeft:
				mAnimator->PlayAnimation(L"ValkThrowUpDown", false);
				break;
			case ss::ValkyrieScript::eDirState::Right:
				mAnimator->PlayAnimation(L"ValkThrowUpRight", false);
				break;
			case ss::ValkyrieScript::eDirState::Left:
				mAnimator->PlayAnimation(L"ValkThrowUpLeft", false);
				break;
			default:
				break;
			}

			if (mAnimator->GetActiveAnimation()->IsComplete())
			{
				mRainStage++;
				WalkAni();
			}
		}
		else if (mRainStage == 2)
		{
			mRain = new SpearRain();
			mRain->GetComponent<Transform>()->SetPosition(mRainTargetPos);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, mRain);
			mRainStage++;
			
		}
		else if (mRainStage == 3)
		{
			if (mRain->GetAniComplete())
				mRainStage++;
		}
		else if (mRainStage == 4)
		{
			mInterval -= Time::DeltaTime();
			if (mInterval > 0.f)
				return;

			mInterval = math::RandomUniDist(0.005f, 0.01f);

			SpearPiece* piece = new SpearPiece();
			Vector3 piecePos;
			piecePos.y = mRainTargetPos.y + 2.5f + math::RandomUniDist(-0.5f, 0.5f);
			piecePos.x = mRainTargetPos.x + math::RandomUniDist(-0.5f, 0.5f);
			piece->GetComponent<Transform>()->SetPosition(piecePos);

			SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, piece);

			mPieceCount++;
			if (mPieceCount >= 100)
			{
				mRainStage++;
				mPieceCount = 0;
			}
		}
		else if (mRainStage == 5)
		{
			mRainStage = 0;
			mState = eState::Chase;
		}
	}

	void ValkyrieScript::ChangeHP(float value)
	{
		mHp += value;
	}

	void ValkyrieScript::DamageCheck()
	{
		float value = GetOwner()->GetChangeHpValue();
		if (value != 0)
		{
			mHp += value;
			GetOwner()->SetChangeHpValue(0.f);
		}
	}

	void ValkyrieScript::CalDir(Vector3 targetPos)
	{
		float degree = math::CalculateDegree(Vector2(mPos.x, mPos.y), Vector2(targetPos.x, targetPos.y));

		if (-22.5f <= degree && degree < 22.5f)
			mDirState = eDirState::Right;
		else if (22.5f <= degree && degree < 67.5f)
			mDirState = eDirState::UpRight;
		else if (67.5f <= degree && degree < 112.5f)
			mDirState = eDirState::Up;
		else if (112.5f <= degree && degree < 157.5f)
			mDirState = eDirState::UpLeft;
		else if (157.5f <= degree || degree < -157.5f)
			mDirState = eDirState::Left;
		else if (-157.5f <= degree && degree < -112.5f)
			mDirState = eDirState::DownLeft;
		else if (-112.5f <= degree && degree < -67.5f)
			mDirState = eDirState::Down;
		else if (-67.5 <= degree && degree < -22.5)
			mDirState = eDirState::DownRight;
	}

	void ValkyrieScript::ChangeColSetting()
	{
		switch (mColState)
		{
		case ss::ValkyrieScript::eColideState::Normal:
			mCollider->SetCollideType(eCollideType::NormalMonster);
			break;
		case ss::ValkyrieScript::eColideState::Rush:
			mCollider->SetCollideType(eCollideType::Projectile);
			break;
		default:
			break;
		}
	}

	void ValkyrieScript::Pattern()
	{
		mPatternTime += Time::DeltaTime();
		if (mPatternTime < 0.6f)
			return;

		mPatternTime = 0.f;

		if (mPatternNum == 0)
		{
			mState = eState::LightningRush;
			mPatternNum++;
		}
		else if (mPatternNum == 1)
		{
			mState = eState::ThrowRightBall;
			mPatternNum++;
		}
		else if (mPatternNum == 2)
		{
			mState = eState::LightningAssault;
			mPatternNum++;
		}
		else if (mPatternNum == 3)
		{
			mState = eState::LightningRush;
			mPatternNum++;
		}
		else if (mPatternNum == 4)
		{
			mState = eState::SpearRainCast;
			mPatternNum++;
		}
		else if (mPatternNum == 5)
		{
			mState = eState::ThrowRightBall;
			mPatternNum = 0;
		}
	}

	void ValkyrieScript::Pattern2()
	{
		mPatternTime += Time::DeltaTime();
		if (mPatternTime < 0.4f)
			return;

		mPatternTime = 0.f;

		if (mPatternNum == 0)
		{
			mState = eState::CloneAssault;
			mPatternNum++;
		}
		else if (mPatternNum == 1)
		{
			mState = eState::ThrowRightBall;
			mPatternNum++;
		}
		else if (mPatternNum == 2)
		{
			mState = eState::BigLightning;
			mPatternNum++;
		}
		else if (mPatternNum == 3)
		{
			mState = eState::CloneAssault;
			mPatternNum++;
		}
		else if (mPatternNum == 4)
		{
			mState = eState::LightningRush;
			mPatternNum++;
		}
		else if (mPatternNum == 5)
		{
			mState = eState::SpearRainCast;
			mPatternNum++;
		}
		else if (mPatternNum == 6)
		{
			mState = eState::LightningAssault;
			mPatternNum = 0;
		}
	}

	void ValkyrieScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player
			&& mColState == eColideState::Rush)
		{
			dynamic_cast<Player*>(other->GetOwner())->GetScript()->ChangeHp(-300.f);
		}
		else if (other->GetCollideType() == eCollideType::Player
			&& mColState == eColideState::Assault)
		{
			dynamic_cast<Player*>(other->GetOwner())->GetScript()->ChangeHp(-550.f);
		}
	}
	void ValkyrieScript::OnCollisionStay(Collider2D* other)
	{
		
	}
	void ValkyrieScript::OnCollisionExit(Collider2D* other)
	{
	}
}