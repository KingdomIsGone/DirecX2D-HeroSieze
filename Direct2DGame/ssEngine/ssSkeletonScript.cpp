#include "ssSkeletonScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"
#include "ssPlayerScript.h"

namespace ss
{
	SkeletonScript::SkeletonScript()
		: mAgroDistance(1.8f)
		, mSpeed(0.5f)
		, mHp(1000.0f)
		, mDamage(80.0f)
	{
	}
	SkeletonScript::~SkeletonScript()
	{
	}
	void SkeletonScript::Initialize()
	{
		mState = eState::Idle;
		mDirState = eDirState::Down;
		mAnimator = GetOwner()->GetComponent<Animator>();
		


	}

	void SkeletonScript::Update()
	{
		mPlayerPos = PlayerScript::GetPlayerPos();
		mPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (mHp <= 0)
		{
			GetOwner()->SetState(GameObject::eState::Dead);
		}

		switch (mState)
		{
		case ss::SkeletonScript::eState::Idle:
			Idle();
			break;
		case ss::SkeletonScript::eState::Chase:
			Chase();
			break;
		case ss::SkeletonScript::eState::Attack:
			Attack();
			break;
		case ss::SkeletonScript::eState::Dead:
			break;
		default:
			break;
		}
	}

	void SkeletonScript::Idle()
	{
		float distance = math::GetDistance(mPos, mPlayerPos);

		if (distance < mAgroDistance)
			mState = eState::Chase;
	}
	void SkeletonScript::Chase()
	{
		if (mPos.x < mPlayerPos.x)
			mPos.x += mSpeed * Time::DeltaTime();
		else
			mPos.x -= mSpeed * Time::DeltaTime();

		if (mPos.y < mPlayerPos.y)
			mPos.y += mSpeed * Time::DeltaTime();
		else
			mPos.y -= mSpeed * Time::DeltaTime();

		if (mIsColliding)
			mPos = ReverseMove();

		GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

		PlayMoveAni();

		float distance = math::GetDistance(mPos, mPlayerPos);

		/*if (distance < 0.005f)
			mState = eState::Attack;*/
	}

	void SkeletonScript::Attack()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		switch (mDirState)
		{
		case ss::SkeletonScript::eDirState::Up:
			mAnimator->PlayAnimation(L"Skeleton_UpAtk", false);
			break;
		case ss::SkeletonScript::eDirState::Down:
			mAnimator->PlayAnimation(L"Skeleton_DownAtk", false);
			break;
		case ss::SkeletonScript::eDirState::Left:
			mAnimator->PlayAnimation(L"Skeleton_LeftAtk", false);
			break;
		case ss::SkeletonScript::eDirState::Right:
			mAnimator->PlayAnimation(L"Skeleton_RightAtk", false);
			break;
		default:
			break;
		}

		if (mAnimator->GetActiveAnimation()->IsComplete())
		{
			Damage();
			mAnimator->GetActiveAnimation()->Reset();
		}
		

		float distance = math::GetDistance(mPos, mPlayerPos);
		if (distance > 0.5f && !mIsColliding)
			mState = eState::Chase;
	}

	void SkeletonScript::PlayMoveAni()
	{
		if (abs(mPos.x - mPlayerPos.x) < 0.5f)
			mXAccess = true;
		else
			mXAccess = false;

		if (abs(mPos.y - mPlayerPos.y) < 0.7f)
			mYAccess = true;
		else
			mYAccess = false;

		if (mPos.y < mPlayerPos.y && !mYAccess)
			mDirState = eDirState::Up;
		else if (mPos.y > mPlayerPos.y && !mYAccess)
			mDirState = eDirState::Down;
		else if (mPos.x > mPlayerPos.x && !mXAccess)
			mDirState = eDirState::Left;
		else if (mPos.x < mPlayerPos.x && !mXAccess)
			mDirState = eDirState::Right;

		mAnimator = GetOwner()->GetComponent<Animator>();
		switch (mDirState)
		{
		case ss::SkeletonScript::eDirState::Up:
			mAnimator->PlayAnimation(L"SkeletonUp", true);
			break;
		case ss::SkeletonScript::eDirState::Down:
			mAnimator->PlayAnimation(L"SkeletonDown", true);
			break;
		case ss::SkeletonScript::eDirState::Left:
			mAnimator->PlayAnimation(L"SkeletonLeft", true);
			break;
		case ss::SkeletonScript::eDirState::Right:
			mAnimator->PlayAnimation(L"SkeletonRight", true);
			break;
		default:
			break;
		}
	}

	Vector3 SkeletonScript::ReverseMove()
	{
		if (mPos.x < mPlayerPos.x)
			mPos.x -= mSpeed * Time::DeltaTime();
		else
			mPos.x += mSpeed * Time::DeltaTime();

		if (mPos.y < mPlayerPos.y)
			mPos.y += mSpeed * Time::DeltaTime();
		else
			mPos.y -= mSpeed * Time::DeltaTime();

		return mPos;
	}

	float SkeletonScript::CalculateMoveDegree(Vector3 monsterpos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(monsterpos.x, monsterpos.y), Vector2(point.x, point.y));

		return degree;
	}

	void SkeletonScript::Damage()
	{
		PlayerScript::ChangeHp(-mDamage);
	}

	void SkeletonScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
			mState = eState::Attack;

		/*if (other->GetCollideType() == eCollideType::Projectile)
		{
			if (other->GetOwner()->GetName() == L"FireBall")
			{
				mHp -= dynamic_cast<FireBall*>(other)->GetDamage();
			}
		}*/
	}
	void SkeletonScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
			mState = eState::Attack;
	}
	void SkeletonScript::OnCollisionExit(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
			mState = eState::Chase;
	}
}