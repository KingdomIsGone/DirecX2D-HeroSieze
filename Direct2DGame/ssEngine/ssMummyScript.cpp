#include "ssMummyScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssResources.h"
#include "ssAudioClip.h"
#include "ssAudioSource.h"

namespace ss
{
	MummyScript::MummyScript()
		: mAgroDistance(2.5f)
		, mSpeed(0.2f)
		, mHp(500.0f)
		, mDamage(50.f)
	{
	}
	MummyScript::~MummyScript()
	{
		ColideClear();
	}
	void MummyScript::Initialize()
	{
		mState = eState::Idle;
		mDirState = eDirState::Down;
		mAnimator = GetOwner()->GetComponent<Animator>();
		mCollider = GetOwner()->GetComponent<Collider2D>();

		GameObject* audioSpeaker = new GameObject();
		mAs = audioSpeaker->AddComponent<AudioSource>();
		mAs->SetClip(Resources::Load<AudioClip>(L"MummySound", L"..\\Resources\\Sound\\MonsterAtk\\MummyAtk.wav"));

	}

	void MummyScript::Update()
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
		case ss::MummyScript::eState::Idle:
			Idle();
			break;
		case ss::MummyScript::eState::Chase:
			Chase();
			break;
		case ss::MummyScript::eState::Attack:
			Attack();
			break;
		case ss::MummyScript::eState::Dead:
			break;
		default:
			break;
		}
	}

	void MummyScript::Idle()
	{
		float distance = math::GetDistance(mPos, mPlayerPos);

		if (distance < mAgroDistance)
			mState = eState::Chase;
	}
	void MummyScript::Chase()
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


		//float distance = math::GetDistance(mPos, mPlayerPos);
		/*if (distance < 0.005f)
			mState = eState::Attack;*/
	}

	void MummyScript::Attack()
	{
		CalculateMoveDegree(mPos, mPlayerPos);

		switch (mDirState)
		{
		case ss::MummyScript::eDirState::Up:
			mAnimator->PlayAnimation(L"MummyUpAtk", true);
			break;
		case ss::MummyScript::eDirState::Down:
			mAnimator->PlayAnimation(L"MummyDownAtk", true);
			break;
		case ss::MummyScript::eDirState::Left:
			mAnimator->PlayAnimation(L"MummyLeftAtk", true);
			break;
		case ss::MummyScript::eDirState::Right:
			mAnimator->PlayAnimation(L"MummyRightAtk", true);
			break;
		default:
			break;
		}

		if (mAnimator->GetActiveAnimation()->IsComplete())
		{
			mAs->SetClip(Resources::Find<AudioClip>(L"MummySound"));
			mAs->Play();

			Damage();
			mAnimator->GetActiveAnimation()->Reset();
		}

		float distance = math::GetDistance(mPos, mPlayerPos);
		if (distance > 0.3f && !mIsColliding)
			mState = eState::Chase;
	}

	void MummyScript::PlayMoveAni()
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
		case ss::MummyScript::eDirState::Up:
			mAnimator->PlayAnimation(L"MummyUp", true);
			break;
		case ss::MummyScript::eDirState::Down:
			mAnimator->PlayAnimation(L"MummyDown", true);
			break;
		case ss::MummyScript::eDirState::Left:
			mAnimator->PlayAnimation(L"MummyLeft", true);
			break;
		case ss::MummyScript::eDirState::Right:
			mAnimator->PlayAnimation(L"MummyRight", true);
			break;
		default:
			break;
		}
	}

	void MummyScript::Damage()
	{
		PlayerScript::ChangeHp(-mDamage);
	}

	Vector3 MummyScript::ReverseMove()
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

	float MummyScript::CalculateMoveDegree(Vector3 monsterpos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(monsterpos.x, monsterpos.y), Vector2(point.x, point.y));

		return degree;
	}

	void MummyScript::ColideClear()
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

	void MummyScript::DamageCheck()
	{
		float value = GetOwner()->GetChangeHpValue();
		if (value != 0)
		{
			mHp += value;
			GetOwner()->SetChangeHpValue(0.f);
		}
	}

	void MummyScript::OnCollisionEnter(Collider2D* other)
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
	void MummyScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
			mState = eState::Attack;
	}
	void MummyScript::OnCollisionExit(Collider2D* other)
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
