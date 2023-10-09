#include "ssHydraScript.h"
#include "ssGameObject.h"
#include "ssTime.h"
#include "ssFireBall.h"
#include "ssSceneManager.h"
#include "ssHydra.h"

namespace ss
{
	HydraScript::HydraScript()
		: mDamage(150.0f)
		, mTime(4.5f)
		, mTargetPos(Vector3(0.0f, 0.0f, 999.f))
	{
		mDirState = eDirState::Down;
	}
	HydraScript::~HydraScript()
	{
	}
	void HydraScript::Initialize()
	{
	}
	void HydraScript::Update()
	{
		mHydraPos = mHydra->GetComponent<Transform>()->GetPosition();
		CalDir(mTargetPos);
		if (!mOnAttack)
			PlayStandAni();
		else
			PlayAtkAni();


	}
	void HydraScript::OnCollisionEnter(Collider2D* other)
	{

	}
	void HydraScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::NormalMonster)
		{
			mTime += Time::DeltaTime();

			if (mTime < 4.5f)
			{
				CalDir(mTargetPos);

				return;
			}
			else
			{
				mOnAttack = true;
				mTargetPos = other->GetOwner()->GetComponent<Transform>()->GetPosition();
				CalDir(mTargetPos);
				PlayAtkAni();

				if (mHydra->GetAnimator()->GetActiveAnimation()->IsComplete())
				{
					mTime = 0.0f;
					AttackFireBall(mHydraPos, mTargetPos);
					mOnAttack = false;
					PlayStandAni();
				}
			}
		}
	}
	void HydraScript::OnCollisionExit(Collider2D* other)
	{
	}


	void HydraScript::AttackFireBall(Vector3 hydraPos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(hydraPos.x, hydraPos.y), Vector2(point.x, point.y));
		FireBall* fireBall = new FireBall(degree);
		fireBall->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, fireBall);
	}

	void HydraScript::CalDir(Vector3 targetPos)
	{
		float degree= math::CalculateDegree(Vector2(mHydraPos.x, mHydraPos.y), Vector2(targetPos.x, targetPos.y));

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
	void HydraScript::PlayAtkAni()
	{
		switch (mDirState)
		{
		case ss::HydraScript::eDirState::Down:
			mHydra->GetAnimator()->PlayAnimation(L"HydraAtkDown", false);
			break;
		case ss::HydraScript::eDirState::DownLeft:
			mHydra->GetAnimator()->PlayAnimation(L"HydraAtkDownLeft", false);
			break;
		case ss::HydraScript::eDirState::DownRight:
			mHydra->GetAnimator()->PlayAnimation(L"HydraAtkDownRight", false);
			break;
		case ss::HydraScript::eDirState::Right:
			mHydra->GetAnimator()->PlayAnimation(L"HydraAtkRight", false);
			break;
		case ss::HydraScript::eDirState::Left:
			mHydra->GetAnimator()->PlayAnimation(L"HydraAtkLeft", false);
			break;
		case ss::HydraScript::eDirState::UpLeft:
			mHydra->GetAnimator()->PlayAnimation(L"HydraAtkUpLeft", false);
			break;
		case ss::HydraScript::eDirState::UpRight:
			mHydra->GetAnimator()->PlayAnimation(L"HydraAtkUpRight", false);
			break;
		case ss::HydraScript::eDirState::Up:
			mHydra->GetAnimator()->PlayAnimation(L"HydraAtkUp", false);
			break;
		default:
			break;
		}
		
	}
	void HydraScript::PlayStandAni()
	{
		switch (mDirState)
		{
		case ss::HydraScript::eDirState::Down:
			mHydra->GetAnimator()->PlayAnimation(L"HydraStandDown", true);
			break;
		case ss::HydraScript::eDirState::DownLeft:
			mHydra->GetAnimator()->PlayAnimation(L"HydraStandDownLeft", true);
			break;
		case ss::HydraScript::eDirState::DownRight:
			mHydra->GetAnimator()->PlayAnimation(L"HydraStandDownRight", true);
			break;
		case ss::HydraScript::eDirState::Right:
			mHydra->GetAnimator()->PlayAnimation(L"HydraStandRight", true);
			break;
		case ss::HydraScript::eDirState::Left:
			mHydra->GetAnimator()->PlayAnimation(L"HydraStandLeft", true);
			break;
		case ss::HydraScript::eDirState::UpLeft:
			mHydra->GetAnimator()->PlayAnimation(L"HydraStandUpLeft", true);
			break;
		case ss::HydraScript::eDirState::UpRight:
			mHydra->GetAnimator()->PlayAnimation(L"HydraStandUpRight", true);
			break;
		case ss::HydraScript::eDirState::Up:
			mHydra->GetAnimator()->PlayAnimation(L"HydraStandUp", true);
			break;
		default:
			break;
		}
	}
	
}
