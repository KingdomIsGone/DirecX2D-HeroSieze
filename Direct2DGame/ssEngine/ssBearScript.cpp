#include "ssBearScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"
#include "ssPlayerScript.h"
#include "ssCollider2D.h"
#include "ssResources.h"

namespace ss
{
	BearScript::BearScript()
		: mAgroDistance(1.8f)
		, mSpeed(0.5f)
		, mHp(2200.0f)
		, mDamage(120.0f)
		, mDamage2(240.f)
		, mAtkCount(0)
	{
	}
	BearScript::~BearScript()
	{
		ColideClear();
	}
	void BearScript::Initialize()
	{
		mState = eState::Idle;
		mDirState = eDirState::Down;
		mAnimator = GetOwner()->GetComponent<Animator>();
		mCollider = GetOwner()->GetComponent<Collider2D>();
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
		{
			if (mAtkCount < 2)
				Attack();
			else
				Attack2();
			break;
		}
		case ss::BearScript::eState::Dead:
			Dead();
			break;
		default:
			break;
		}
	}

	void BearScript::Idle()
	{
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

		mPos = ReverseMove();

		GetOwner()->GetComponent<Transform>()->SetPosition(mPos);

		PlayMoveAni();

		//float distance = math::GetDistance(mPos, mPlayerPos);

		/*if (distance < 0.005f)
			mState = eState::Attack;*/
	}

	void BearScript::Attack()
	{
		CalculateMoveDegree(mPos, mPlayerPos);

		switch (mDirState)
		{
		case ss::BearScript::eDirState::Up:
			mAnimator->PlayAnimation(L"Bear_UpAtk", false);
			break;
		case ss::BearScript::eDirState::Down:
			mAnimator->PlayAnimation(L"Bear_DownAtk", false);
			break;
		case ss::BearScript::eDirState::Left:
			mAnimator->PlayAnimation(L"Bear_LeftAtk", false);
			break;
		case ss::BearScript::eDirState::Right:
			mAnimator->PlayAnimation(L"Bear_RightAtk", false);
			break;
		default:
			break;
		}

		if (mAnimator->GetActiveAnimation()->IsComplete())
		{
			mAtkCount++;
			PlayerScript::ChangeHp(-mDamage);
			mAnimator->GetActiveAnimation()->Reset();
		}


		float distance = math::GetDistance(mPos, mPlayerPos);
		if (distance > 0.5f && !mIsColliding)
			mState = eState::Chase;
	}

	void BearScript::Attack2()
	{
		CalculateMoveDegree(mPos, mPlayerPos);

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
			PlayerScript::ChangeHp(-mDamage2);
			mAnimator->GetActiveAnimation()->Reset();
		}


		float distance = math::GetDistance(mPos, mPlayerPos);
		if (distance > 0.5f && !mIsColliding)
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

		if(mAnimator->GetActiveAnimation()->IsComplete())
			GetOwner()->SetState(GameObject::eState::Dead);
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

	

	Vector3 BearScript::ReverseMove()
	{
		if (mCollider->GetDirCount(e4Direction::Left) > 0)
		{
			if (mPos.x > mPlayerPos.x)
				mPos.x += (mSpeed + 0.f) * Time::DeltaTime();
		}

		if (mCollider->GetDirCount(e4Direction::Right) > 0)
		{
			if (mPos.x < mPlayerPos.x)
				mPos.x -= (mSpeed + 0.f) * Time::DeltaTime();
		}

		if (mCollider->GetDirCount(e4Direction::Up) > 0)
		{
			if (mPos.y < mPlayerPos.y)
				mPos.y -= (mSpeed + 0.f) * Time::DeltaTime();
		}

		if (mCollider->GetDirCount(e4Direction::Down) > 0)
		{
			if (mPos.y > mPlayerPos.y)
				mPos.y += (mSpeed + 0.f) * Time::DeltaTime();
		}

		return mPos;
	}

	float BearScript::CalculateMoveDegree(Vector3 monsterpos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(monsterpos.x, monsterpos.y), Vector2(point.x, point.y));

		return degree;
	}

	void BearScript::ColideClear()
	{
		for (auto iter = mColAdressMap.begin(); iter != mColAdressMap.end(); iter++)
		{
			UINT colNum = iter->second->GetColDir();

			if (colNum == 1)
				iter->second->SetDirCountMinus(e4Direction::Up);
			else if (colNum == 2)
				iter->second->SetDirCountMinus(e4Direction::Down);
			else if (colNum == 3)
				iter->second->SetDirCountMinus(e4Direction::Left);
			else if (colNum == 4)
				iter->second->SetDirCountMinus(e4Direction::Right);
		}
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
			mState = eState::Attack;

		if (other->GetCollideType() == eCollideType::Player
			|| other->GetCollideType() == eCollideType::NormalMonster
			|| other->GetCollideType() == eCollideType::SpecialMonster
			|| other->GetCollideType() == eCollideType::Wall)
		{
			UINT colNum = other->GetColDir();
			UINT colID = other->GetColliderID();

			if (mColDirMap.find(colID) != mColDirMap.end())
				return;

			if (colNum == 1)
				mCollider->SetDirCountPlus(e4Direction::Down);
			else if (colNum == 2)
				mCollider->SetDirCountPlus(e4Direction::Up);
			else if (colNum == 3)
				mCollider->SetDirCountPlus(e4Direction::Right);
			else if (colNum == 4)
				mCollider->SetDirCountPlus(e4Direction::Left);

			mColDirMap[colID] = colNum;
			mColAdressMap[colID] = other;
		}

	}
	void BearScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
			mState = eState::Attack;

	}
	void BearScript::OnCollisionExit(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
			mState = eState::Chase;

		if (other->GetCollideType() == eCollideType::Player
			|| other->GetCollideType() == eCollideType::NormalMonster
			|| other->GetCollideType() == eCollideType::SpecialMonster
			|| other->GetCollideType() == eCollideType::Wall)
		{
			UINT colNum = mColDirMap[other->GetColliderID()];

			if (colNum == 1)
				mCollider->SetDirCountMinus(e4Direction::Down);
			else if (colNum == 2)
				mCollider->SetDirCountMinus(e4Direction::Up);
			else if (colNum == 3)	  
				mCollider->SetDirCountMinus(e4Direction::Right);
			else if (colNum == 4)	  
				mCollider->SetDirCountMinus(e4Direction::Left);

			mColDirMap.erase(other->GetColliderID());
			mColAdressMap.erase(other->GetColliderID());
		}


	}
}