#include "ssEntScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"

namespace ss
{
	EntScript::EntScript()
		: mAgroDistance(1.8f)
		, mSpeed(0.5f)
		, mHp(1000.0f)
		, mDamage(80.0f)
	{
	}
	EntScript::~EntScript()
	{
	}
	void EntScript::Initialize()
	{
		mState = eState::Idle;
		mDirState = eDirState::Down;
		mAnimator = GetOwner()->GetComponent<Animator>();
	}

	void EntScript::Update()
	{
		mPlayerPos = PlayerScript::GetPlayerPos();
		mPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		DamageCheck();
		if (mHp <= 0)
		{
			GetOwner()->SetState(GameObject::eState::Dead);
		}

		switch (mState)
		{
		case ss::EntScript::eState::Idle:
			Idle();
			break;
		case ss::EntScript::eState::Chase:
			Chase();
			break;
		case ss::EntScript::eState::Attack:
			Attack();
			break;
		case ss::EntScript::eState::Dead:
			break;
		default:
			break;
		}
	}

	void EntScript::Idle()
	{
		float distance = math::GetDistance(mPos, mPlayerPos);

		if (distance < mAgroDistance)
			mState = eState::Chase;
	}
	void EntScript::Chase()
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

	void EntScript::Attack()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		switch (mDirState)
		{
		case ss::EntScript::eDirState::Up:
			mAnimator->PlayAnimation(L"Ent_AtkUp", false);
			break;
		case ss::EntScript::eDirState::Down:
			mAnimator->PlayAnimation(L"Ent_AtkDown", false);
			break;
		case ss::EntScript::eDirState::Left:
			mAnimator->PlayAnimation(L"Ent_AtkLeft", false);
			break;
		case ss::EntScript::eDirState::Right:
			mAnimator->PlayAnimation(L"Ent_AtkRight", false);
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

	void EntScript::PlayMoveAni()
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
		case ss::EntScript::eDirState::Up:
			mAnimator->PlayAnimation(L"Ent_Up", true);
			break;
		case ss::EntScript::eDirState::Down:
			mAnimator->PlayAnimation(L"Ent_Down", true);
			break;
		case ss::EntScript::eDirState::Left:
			mAnimator->PlayAnimation(L"Ent_Left", true);
			break;
		case ss::EntScript::eDirState::Right:
			mAnimator->PlayAnimation(L"Ent_Right", true);
			break;
		default:
			break;
		}
	}

	Vector3 EntScript::ReverseMove()
	{
		if (mLeftColCount > 0)
		{
			if (mPos.x > mPlayerPos.x)
				mPos.x += (mSpeed + 0.f) * Time::DeltaTime();
		}

		if (mRightColCount > 0)
		{
			if (mPos.x < mPlayerPos.x)
				mPos.x -= (mSpeed + 0.f) * Time::DeltaTime();
		}

		if (mTopColCount > 0)
		{
			if (mPos.y < mPlayerPos.y)
				mPos.y -= (mSpeed + 0.f) * Time::DeltaTime();
		}

		if (mBottomColCount > 0)
		{
			if (mPos.y > mPlayerPos.y)
				mPos.y += (mSpeed + 0.f) * Time::DeltaTime();
		}

		return mPos;
	}

	float EntScript::CalculateMoveDegree(Vector3 monsterpos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(monsterpos.x, monsterpos.y), Vector2(point.x, point.y));

		return degree;
	}

	void EntScript::Damage()
	{
		PlayerScript::ChangeHp(-mDamage);
	}

	void EntScript::DamageCheck()
	{
		float value = GetOwner()->GetChangeHpValue();
		if (value != 0)
		{
			mHp += value;
			GetOwner()->SetChangeHpValue(0.f);
		}
	}

	void EntScript::OnCollisionEnter(Collider2D* other)
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
	void EntScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
			mState = eState::Attack;
	}
	void EntScript::OnCollisionExit(Collider2D* other)
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