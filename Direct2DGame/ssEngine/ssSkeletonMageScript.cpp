#include "ssSkeletonMageScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"
#include "ssSceneManager.h"
#include "ssMagicBall.h"
#include "ssCollider2D.h"
#include "ssResources.h"

namespace ss
{
	SkeletonMageScript::SkeletonMageScript()
		: mAgroDistance(2.6f)
		, mSpeed(0.5f)
		, mHp(1000.0f)
	{
		ColideClear();
	}
	SkeletonMageScript::~SkeletonMageScript()
	{
	}
	void SkeletonMageScript::Initialize()
	{
		mState = eState::Idle;
		mDirState = eDirState::Down;
		mAnimator = GetOwner()->GetComponent<Animator>();
		mCollider = GetOwner()->GetComponent<Collider2D>();
	}

	void SkeletonMageScript::Update()
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
		case ss::SkeletonMageScript::eState::Idle:
			Idle();
			break;
		case ss::SkeletonMageScript::eState::Chase:
			Chase();
			break;
		case ss::SkeletonMageScript::eState::Attack:
			Attack();
			break;
		case ss::SkeletonMageScript::eState::Dead:
			break;
		default:
			break;
		}
	}

	void SkeletonMageScript::Idle()
	{
		float distance = math::GetDistance(mPos, mPlayerPos);

		if (distance < mAgroDistance)
			mState = eState::Chase;
	}
	void SkeletonMageScript::Chase()
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

	void SkeletonMageScript::Attack()
	{
		CalculateMoveDegree(mPos, mPlayerPos);

		CalDir(mPlayerPos);

		switch (mDirState)
		{
		case ss::SkeletonMageScript::eDirState::Up:
			mAnimator->PlayAnimation(L"SkMageAtkUp", false);
			break;
		case ss::SkeletonMageScript::eDirState::Down:
			mAnimator->PlayAnimation(L"SkMageAtkDown", false);
			break;
		case ss::SkeletonMageScript::eDirState::Left:
			mAnimator->PlayAnimation(L"SkMageAtkLeft", false);
			break;
		case ss::SkeletonMageScript::eDirState::Right:
			mAnimator->PlayAnimation(L"SkMageAtkRight", false);
			break;
		default:
			break;
		}

		if (mAnimator->GetActiveAnimation()->IsComplete())
		{
			float degree = CalculateMoveDegree(mPos, mPlayerPos);
			MagicBall* ball = new MagicBall(degree);

			Vector3 pos = mPos;
			pos.z -= 0.1f;
			ball->GetComponent<Transform>()->SetPosition(pos);

			SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, ball);

			mAnimator->GetActiveAnimation()->Reset();
		}


		float distance = math::GetDistance(mPos, mPlayerPos);
		if (distance > 2.0f && !mIsColliding)
			mState = eState::Chase;
	}

	void SkeletonMageScript::PlayMoveAni()
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
		case ss::SkeletonMageScript::eDirState::Up:
			mAnimator->PlayAnimation(L"SkMageWalkUp", true);
			break;
		case ss::SkeletonMageScript::eDirState::Down:
			mAnimator->PlayAnimation(L"SkMageWalkDown", true);
			break;
		case ss::SkeletonMageScript::eDirState::Left:
			mAnimator->PlayAnimation(L"SkMageWalkLeft", true);
			break;
		case ss::SkeletonMageScript::eDirState::Right:
			mAnimator->PlayAnimation(L"SkMageWalkRight", true);
			break;
		default:
			break;
		}
	}

	void SkeletonMageScript::CalDir(Vector3 targetPos)
	{
		float degree = math::CalculateDegree(Vector2(mPos.x, mPos.y), Vector2(targetPos.x, targetPos.y));

		if (-45.f <= degree && degree < 45.f)
			mDirState = eDirState::Right;
		else if (45.f <= degree && degree < 135.f)
			mDirState = eDirState::Up;
		else if (135.f <= degree || degree < -135.f)
			mDirState = eDirState::Left;
		else if (-135.f <= degree && degree < -45.f)
			mDirState = eDirState::Down;
	}

	Vector3 SkeletonMageScript::ReverseMove()
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

	float SkeletonMageScript::CalculateMoveDegree(Vector3 monsterpos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(monsterpos.x, monsterpos.y), Vector2(point.x, point.y));

		return degree;
	}

	void SkeletonMageScript::ColideClear()
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


	void SkeletonMageScript::DamageCheck()
	{
		float value = GetOwner()->GetChangeHpValue();
		if (value != 0)
		{
			mHp += value;
			GetOwner()->SetChangeHpValue(0.f);
		}
	}

	void SkeletonMageScript::OnCollisionEnter(Collider2D* other)
	{
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
	void SkeletonMageScript::OnCollisionStay(Collider2D* other)
	{
	}
	void SkeletonMageScript::OnCollisionExit(Collider2D* other)
	{
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