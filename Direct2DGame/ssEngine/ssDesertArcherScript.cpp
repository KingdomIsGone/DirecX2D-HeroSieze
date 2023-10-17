#include "ssDesertArcherScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"
#include "ssArrow.h"
#include "ssSceneManager.h"

namespace ss
{
	DesertArcherScript::DesertArcherScript()
		: mAgroDistance(2.6f)
		, mSpeed(0.5f)
		, mHp(1000.0f)
	{
	}
	DesertArcherScript::~DesertArcherScript()
	{
	}
	void DesertArcherScript::Initialize()
	{
		mState = eState::Idle;
		mDirState = eDirState::Down;
		mAnimator = GetOwner()->GetComponent<Animator>();

	}

	void DesertArcherScript::Update()
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
		case ss::DesertArcherScript::eState::Idle:
			Idle();
			break;
		case ss::DesertArcherScript::eState::Chase:
			Chase();
			break;
		case ss::DesertArcherScript::eState::Attack:
			Attack();
			break;
		case ss::DesertArcherScript::eState::Dead:
			break;
		default:
			break;
		}
	}

	void DesertArcherScript::Idle()
	{
		float distance = math::GetDistance(mPos, mPlayerPos);

		if (distance < mAgroDistance)
			mState = eState::Chase;
	}
	void DesertArcherScript::Chase()
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

		float distance = math::GetDistance(mPos, mPlayerPos);

		if (distance <= 2.0f)
			mState = eState::Attack;
	}

	void DesertArcherScript::Attack()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();

		switch (mDirState)
		{
		case ss::DesertArcherScript::eDirState::Up:
			mAnimator->PlayAnimation(L"ArcherAtkUp", false);
			break;
		case ss::DesertArcherScript::eDirState::Down:
			mAnimator->PlayAnimation(L"ArcherAtkDown", false);
			break;
		case ss::DesertArcherScript::eDirState::Left:
			mAnimator->PlayAnimation(L"ArcherAtkLeft", false);
			break;
		case ss::DesertArcherScript::eDirState::Right:
			mAnimator->PlayAnimation(L"ArcherAtkRight", false);
			break;
		default:
			break;
		}

		if (mAnimator->GetActiveAnimation()->IsComplete())
		{
			float degree = CalculateMoveDegree(mPos, mPlayerPos);
			Arrow* arrow = new Arrow(degree);

			Vector3 pos = mPos;
			pos.z -= 0.1f;
			arrow->GetComponent<Transform>()->SetPosition(pos);

			SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, arrow);

			mAnimator->GetActiveAnimation()->Reset();
		}


		float distance = math::GetDistance(mPos, mPlayerPos);
		if (distance > 2.0f && !mIsColliding)
			mState = eState::Chase;
	}

	void DesertArcherScript::PlayMoveAni()
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
		case ss::DesertArcherScript::eDirState::Up:
			mAnimator->PlayAnimation(L"ArcherWalkUp", true);
			break;
		case ss::DesertArcherScript::eDirState::Down:
			mAnimator->PlayAnimation(L"ArcherWalkDown", true);
			break;
		case ss::DesertArcherScript::eDirState::Left:
			mAnimator->PlayAnimation(L"ArcherWalkLeft", true);
			break;
		case ss::DesertArcherScript::eDirState::Right:
			mAnimator->PlayAnimation(L"ArcherWalkRight", true);
			break;
		default:
			break;
		}
	}

	Vector3 DesertArcherScript::ReverseMove()
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

	float DesertArcherScript::CalculateMoveDegree(Vector3 monsterpos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(monsterpos.x, monsterpos.y), Vector2(point.x, point.y));

		return degree;
	}


	void DesertArcherScript::DamageCheck()
	{
		float value = GetOwner()->GetChangeHpValue();
		if (value != 0)
		{
			mHp += value;
			GetOwner()->SetChangeHpValue(0.f);
		}
	}

	void DesertArcherScript::OnCollisionEnter(Collider2D* other)
	{
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
	void DesertArcherScript::OnCollisionStay(Collider2D* other)
	{
	}
	void DesertArcherScript::OnCollisionExit(Collider2D* other)
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