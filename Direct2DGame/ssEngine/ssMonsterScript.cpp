#include "ssMonsterScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"
#include "ssMonsterHpScript.h"

namespace ss
{
	MonsterScript::MonsterScript()
		: mAgroDistance(100.0f)
		, mSpeed(0.5f)
		, mHp(1000.0f)
	{
	}
	MonsterScript::~MonsterScript()
	{
	}
	void MonsterScript::Initialize()
	{
		mState = eState::Idle;
		mDirState = eDirState::Down;
		mAnimator = GetOwner()->GetComponent<Animator>();
	}

	void MonsterScript::Update()
	{
		mPlayerPos = PlayerScript::GetPlayerPos();
		mPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (GetOwner()->GetComponent<MonsterHpScript>()->GetHp() <= 0)
		{
			GetOwner()->SetState(GameObject::eState::Dead);
		}

		switch (mState)
		{
		case ss::MonsterScript::eState::Idle:
			Idle();
			break;
		case ss::MonsterScript::eState::Chase:
			Chase();
			break;
		case ss::MonsterScript::eState::Attack:
			Attack();
			break;
		case ss::MonsterScript::eState::Dead:
			break;
		default:
			break;
		}
	}

	void MonsterScript::Idle()
	{
		float distance = math::GetDistance(mPos, mPlayerPos);

		if (distance < mAgroDistance)
			mState = eState::Chase;
	}
	void MonsterScript::Chase()
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

	void MonsterScript::Attack()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		switch (mDirState)
		{
		case ss::MonsterScript::eDirState::Up:
			mAnimator->PlayAnimation(L"Skeleton_UpAtk", true);
			break;
		case ss::MonsterScript::eDirState::Down:
			mAnimator->PlayAnimation(L"Skeleton_DownAtk", true);
			break;
		case ss::MonsterScript::eDirState::Left:
			mAnimator->PlayAnimation(L"Skeleton_LeftAtk", true);
			break;
		case ss::MonsterScript::eDirState::Right:
			mAnimator->PlayAnimation(L"Skeleton_RightAtk", true);
			break;
		default:
			break;
		}


		float distance = math::GetDistance(mPos, mPlayerPos);
		if (distance > 0.3f && !mIsColliding)
			mState = eState::Chase;
	}

	void MonsterScript::PlayMoveAni()
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
		case ss::MonsterScript::eDirState::Up:
			mAnimator->PlayAnimation(L"SkeletonUp", true);
			break;
		case ss::MonsterScript::eDirState::Down:
			mAnimator->PlayAnimation(L"SkeletonDown", true);
			break;
		case ss::MonsterScript::eDirState::Left:
			mAnimator->PlayAnimation(L"SkeletonLeft", true);
			break;
		case ss::MonsterScript::eDirState::Right:
			mAnimator->PlayAnimation(L"SkeletonRight", true);
			break;
		default:
			break;
		}
	}

	Vector3 MonsterScript::ReverseMove()
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

	float MonsterScript::CalculateMoveDegree(Vector3 monsterpos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(monsterpos.x, monsterpos.y), Vector2(point.x, point.y));

		return degree;
	}

	void MonsterScript::OnCollisionEnter(Collider2D* other)
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
	void MonsterScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
			mState = eState::Attack;
	}
	void MonsterScript::OnCollisionExit(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
			mState = eState::Chase;
	}
}