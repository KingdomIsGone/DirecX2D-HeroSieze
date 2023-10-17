#include "ssBearScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"

namespace ss
{
	BearScript::BearScript()
		: mAgroDistance(2.5f)
		, mSpeed(0.5f)
		, mHp(2200.0f)
		, mDamage(100.f)
		, mDamage2(200.f)
		, mAtkCount(0)
	{
		mState = eState::Idle;
		mDirState = eDirState::Down;
	}
	BearScript::~BearScript()
	{
	}
	void BearScript::Initialize()
	{
	}

	void BearScript::Update()
	{
		mPlayerPos = PlayerScript::GetPlayerPos();
		mPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		DamageCheck();
		if (mHp <= 0)
		{
			mState = eState::Dead;
			
		}

		switch (mState)
		{
		case ss::BearScript::eState::Idle:
			Idle();
			break;
		case ss::BearScript::eState::Chase:
			Chase();
			break;
		case ss::BearScript::eState::Attack:
			Attack();
			break;
		case ss::BearScript::eState::Attack2:
			Attack2();
			break;
		case ss::BearScript::eState::Dead:
			Dead();
			break;
		default:
			break;
		}


	}

	void BearScript::Idle()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->PlayAnimation(L"Bear_Idle", true);

		float distance = math::GetDistance(mPos, mPlayerPos);

		if (distance < mAgroDistance)
			mState = eState::Chase;
	}
	void BearScript::Chase()
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

	}

	void BearScript::Attack()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		switch (mDirState)
		{
		case ss::BearScript::eDirState::Up:
			mAnimator->PlayAnimation(L"Bear_UpAtk", false);
			break;
		case ss::BearScript::eDirState::Down:
			mAnimator->PlayAnimation(L"Bear_DownAtk", false);
			break;
		case ss::BearScript::eDirState::Left:
		{
			mAnimator->PlayAnimation(L"Bear_LeftAtk", false);
		}
			break;
		case ss::BearScript::eDirState::Right:
		{
			mAnimator->PlayAnimation(L"Bear_RightAtk", false);
		}
			break;
		default:
			break;
		}

		if (mAnimator->GetActiveAnimation()->IsComplete())
		{
			mAtkCount++;
			Damage(mDamage);
			mAnimator->GetActiveAnimation()->Reset();
			if (mAtkCount == 2)
			{
				mState = eState::Attack2;
			}
		}

		float distance = math::GetDistance(mPos, mPlayerPos);
		if (distance > 0.3f && !mIsColliding)
			mState = eState::Chase;
	}

	void BearScript::Attack2()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		switch (mDirState)
		{
		case ss::BearScript::eDirState::Up:
			mAnimator->PlayAnimation(L"Bear_UpAtk2", false);
			break;
		case ss::BearScript::eDirState::Down:
			mAnimator->PlayAnimation(L"Bear_DownAtk2", false);
			break;
		case ss::BearScript::eDirState::Left:
			mAnimator->PlayAnimation(L"Bear_LeftAtk2", false);
			break;
		case ss::BearScript::eDirState::Right:
			mAnimator->PlayAnimation(L"Bear_RightAtk2", false);
			break;
		default:
			break;
		}

		if (mAnimator->GetActiveAnimation()->IsComplete())
		{
			mAtkCount = 0;
			Damage(mDamage2);
			mAnimator->GetActiveAnimation()->Reset();
		}

		float distance = math::GetDistance(mPos, mPlayerPos);
		if (distance > 0.3f && !mIsColliding)
			mState = eState::Chase;
	}

	void BearScript::Dead()
	{
		switch (mDirState)
		{
		case ss::BearScript::eDirState::Up:
			mAnimator->PlayAnimation(L"Bear_DieUp", false);
			break;
		case ss::BearScript::eDirState::Down:
			mAnimator->PlayAnimation(L"Bear_DieDown", false);
			break;
		case ss::BearScript::eDirState::Left:
			mAnimator->PlayAnimation(L"Bear_DieLeft", false);
			break;
		case ss::BearScript::eDirState::Right:
			mAnimator->PlayAnimation(L"Bear_DieRight", false);
			break;
		default:
			break;
		}

		if (mAnimator->GetActiveAnimation()->IsComplete())
		{
			GetOwner()->SetState(GameObject::eState::Dead);
		}
	}

	void BearScript::PlayMoveAni()
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
		case ss::BearScript::eDirState::Up:
			mAnimator->PlayAnimation(L"Bear_Up", true);
			break;
		case ss::BearScript::eDirState::Down:
			mAnimator->PlayAnimation(L"Bear_Down", true);
			break;
		case ss::BearScript::eDirState::Left:
			mAnimator->PlayAnimation(L"Bear_Left", true);
			break;
		case ss::BearScript::eDirState::Right:
			mAnimator->PlayAnimation(L"Bear_Right", true);
			break;
		default:
			break;
		}
	}

	void BearScript::Damage(float damage)
	{
		PlayerScript::ChangeHp(-damage);
	}

	Vector3 BearScript::ReverseMove()
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

	float BearScript::CalculateMoveDegree(Vector3 monsterpos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(monsterpos.x, monsterpos.y), Vector2(point.x, point.y));

		return degree;
	}

	void BearScript::DamageCheck()
	{
		float value = GetOwner()->GetChangeHpValue();
		if (value != 0)
		{
			mHp += value;
			GetOwner()->SetChangeHpValue(0.f);
		}
	}

	void BearScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			mState = eState::Attack;
			
		}

		if (other->GetCollideType() == eCollideType::Player
			|| other->GetCollideType() == eCollideType::NormalMonster
			|| other->GetCollideType() == eCollideType::SpecialMonster)
		{
			UINT colNum = other->GetColDir();
			UINT colID = other->GetColliderID();

			if (mColDirMap.find(colID) != mColDirMap.end())
				return;

			if (colNum == 1)
				mBottomColCount++;
			else if (colNum == 2)
				mTopColCount++;
			else if (colNum == 3)
				mRightColCount++;
			else if (colNum == 4)
				mLeftColCount++;

			mColDirMap[colID] = colNum;
		}
	}
	void BearScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			if(mAtkCount <2)
				mState = eState::Attack;
			else if(mAtkCount == 2)
				mState = eState::Attack2;

		}
	}
	void BearScript::OnCollisionExit(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
			mState = eState::Chase;

		if (other->GetCollideType() == eCollideType::Player
			|| other->GetCollideType() == eCollideType::NormalMonster
			|| other->GetCollideType() == eCollideType::SpecialMonster)
		{
			UINT colNum = mColDirMap[other->GetColliderID()];

			if (colNum == 1)
				mBottomColCount--;
			else if (colNum == 2)
				mTopColCount--;
			else if (colNum == 3)
				mRightColCount--;
			else if (colNum == 4)
				mLeftColCount--;

			mColDirMap.erase(other->GetColliderID());
		}
	}
}
