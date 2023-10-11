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

namespace ss
{
	ValkyrieScript::ValkyrieScript()
		: mHp(10000.0f)
		, mSpeed(1.f)
		, mRushStage(0)
		, mRushAxisDist(0.01f)
		, mRushBackDist(0.8f)
		, mRushDistCol(3.2f)
		, mRushDistRow(4.6f)
		, mRushSpeed(4.5f)
		, mEffectCount(0)
	{
	}
	ValkyrieScript::~ValkyrieScript()
	{
	}
	void ValkyrieScript::Initialize()
	{
		//mState = eState::Sleep;
		srand((unsigned int)time(NULL));

		mAnimator = GetOwner()->GetComponent<Animator>();
		mCollider = GetOwner()->GetComponent<Collider2D>();

		mPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		mDirState = eDirState::Down;
	}

	void ValkyrieScript::Update()
	{
		mPlayerPos = PlayerScript::GetPlayerPos();
		mPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		DamageCheck();

		if (mHp <= 0)
			mState = eState::Dead;

		//Chase();
		

		if (Input::GetKey(eKeyCode::O))
		{
			LightningRush();
		}

		if (Input::GetKey(eKeyCode::P))
		{
			LightningAssault();
		}

	}

	void ValkyrieScript::Dead()
	{
		/*GetOwner()->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
		mAnimator->PlayAnimation(L"AnubisDeadEffect", false);

		if (mAnimator->GetActiveAnimation()->IsComplete())
		{
			GetOwner()->SetState(GameObject::eState::Dead);
			dynamic_cast<Anubis*>(GetOwner())->SetDead();
		}*/
	}

	void ValkyrieScript::Chase()
	{
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
				//mState = 
			}
			else if (distance >= mRushDistRow
				&& (mDirState == eDirState::Right || mDirState == eDirState::Left))
			{
				mRushStage = 0;
				mColState = eColideState::Normal;
				ChangeColSetting();
				//mState = 
			}

		}

	}

	void ValkyrieScript::LightningAssault()
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
				else if (mPos.x > mPlayerPos.x && distance > mRushAxisDist)
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

				if (distance < mRushBackDist)
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
			mColState = eColideState::Assault;
			ChangeColSetting();
			float distance;
			if (mDirState == eDirState::Up
				|| mDirState == eDirState::UpRight
				|| mDirState == eDirState::UpLeft)
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
					}
				}

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
				{
					if (mEffectCount == 0)
					{
						mThunderEffect = new ValThunderEffect();
						mThunderEffect->SetValkyrie(mValk);
						mThunderEffect->SetDown();
						SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mThunderEffect);
						mEffectCount++;
					}
				}

				distance = abs(mPos.y - mRushBeforePos.y);

				if (distance < mRushDistCol)
					mPos.y -= mRushSpeed * Time::DeltaTime();
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
					}
				}

				distance = abs(mPos.x - mRushBeforePos.x);

				if (distance < mRushDistRow)
					mPos.x += mRushSpeed * Time::DeltaTime();
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
					}
				}

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
				mEffectCount = 0;
				mThunderEffect->SetDead();
				mThunderEffect = nullptr;
				mColState = eColideState::Normal;
				ChangeColSetting();
				//mState = 
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
				//mState = 
			}

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