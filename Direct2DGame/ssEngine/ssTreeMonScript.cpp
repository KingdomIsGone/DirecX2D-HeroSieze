#include "ssTreeMonScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"
#include "ssSceneManager.h"
#include "ssDart.h"
#include "ssCollider2D.h"
#include "ssResources.h"
#include "ssAudioClip.h"
#include "ssAudioSource.h"

namespace ss
{
	TreeMonScript::TreeMonScript()
		: mAgroDistance(2.6f)
		, mSpeed(0.5f)
		, mHp(1000.0f)
	{
	}
	TreeMonScript::~TreeMonScript()
	{
		ColideClear();
	}
	void TreeMonScript::Initialize()
	{
		mState = eState::Idle;
		mDirState = eDirState::Down;
		mAnimator = GetOwner()->GetComponent<Animator>();
		mCollider = GetOwner()->GetComponent<Collider2D>();

		GameObject* audioSpeaker = new GameObject();
		mAs = audioSpeaker->AddComponent<AudioSource>();
		mAs->SetClip(Resources::Load<AudioClip>(L"TreeMonSound", L"..\\Resources\\Sound\\MonsterAtk\\TreemonAtk.wav"));
	}

	void TreeMonScript::Update()
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
		case ss::TreeMonScript::eState::Idle:
			Idle();
			break;
		case ss::TreeMonScript::eState::Chase:
			Chase();
			break;
		case ss::TreeMonScript::eState::Attack:
			Attack();
			break;
		case ss::TreeMonScript::eState::Dead:
			break;
		default:
			break;
		}
	}

	void TreeMonScript::Idle()
	{
		float distance = math::GetDistance(mPos, mPlayerPos);

		if (distance < mAgroDistance)
			mState = eState::Chase;
	}
	void TreeMonScript::Chase()
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

	void TreeMonScript::Attack()
	{

		CalDir(mPlayerPos);
		switch (mDirState)
		{
		case ss::TreeMonScript::eDirState::Up:
			mAnimator->PlayAnimation(L"TreeMonAtkUp", false);
			break;
		case ss::TreeMonScript::eDirState::Down:
			mAnimator->PlayAnimation(L"TreeMonAtkDown", false);
			break;
		case ss::TreeMonScript::eDirState::Left:
			mAnimator->PlayAnimation(L"TreeMonAtkLeft", false);
			break;
		case ss::TreeMonScript::eDirState::Right:
			mAnimator->PlayAnimation(L"TreeMonAtkRight", false);
			break;
		default:
			break;
		}

		if (mAnimator->GetActiveAnimation()->IsComplete())
		{
			mAs->SetClip(Resources::Find<AudioClip>(L"TreeMonSound"));
			mAs->Play();

			float degree = CalculateMoveDegree(mPos, mPlayerPos);
			Dart* dart = new Dart(degree);

			Vector3 pos = mPos;
			pos.z -= 0.1f;
			dart->GetComponent<Transform>()->SetPosition(pos);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, dart);

			mAnimator->GetActiveAnimation()->Reset();
		}


		float distance = math::GetDistance(mPos, mPlayerPos);
		if (distance > 2.0f && !mIsColliding)
			mState = eState::Chase;
	}

	void TreeMonScript::PlayMoveAni()
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
		case ss::TreeMonScript::eDirState::Up:
			mAnimator->PlayAnimation(L"TreeMonWalkUp", true);
			break;
		case ss::TreeMonScript::eDirState::Down:
			mAnimator->PlayAnimation(L"TreeMonWalkDown", true);
			break;
		case ss::TreeMonScript::eDirState::Left:
			mAnimator->PlayAnimation(L"TreeMonWalkLeft", true);
			break;
		case ss::TreeMonScript::eDirState::Right:
			mAnimator->PlayAnimation(L"TreeMonWalkRight", true);
			break;
		default:
			break;
		}
	}

	void TreeMonScript::CalDir(Vector3 targetPos)
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

	Vector3 TreeMonScript::ReverseMove()
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

	float TreeMonScript::CalculateMoveDegree(Vector3 monsterpos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(monsterpos.x, monsterpos.y), Vector2(point.x, point.y));

		return degree;
	}

	void TreeMonScript::ColideClear()
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


	void TreeMonScript::DamageCheck()
	{
		float value = GetOwner()->GetChangeHpValue();
		if (value != 0)
		{
			mHp += value;
			GetOwner()->SetChangeHpValue(0.f);
		}
	}

	void TreeMonScript::OnCollisionEnter(Collider2D* other)
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
	void TreeMonScript::OnCollisionStay(Collider2D* other)
	{
	}
	void TreeMonScript::OnCollisionExit(Collider2D* other)
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