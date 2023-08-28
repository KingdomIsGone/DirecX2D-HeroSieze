#include "ssPlayerScript.h"
#include "ssCameraScript.h"
#include "ssTransform.h"
#include "ssGameObject.h"
#include "ssTime.h"
#include "ssInput.h"
#include "ssAnimator.h"
#include "ssResources.h"
#include "ssMeshRenderer.h"
#include "ssCursor.h"
#include "ssCamera.h"
#include "ssFireBall.h"
#include "ssSceneManager.h"
#include "ssIndicator.h"
#include "ssCollisionManager.h"
#include "ssMeteor.h"

namespace ss
{
	Vector3 ss::PlayerScript::mPlayerPos = Vector3::Zero;
	float ss::PlayerScript::mSpeed = 2.0f;
	float ss::PlayerScript::mCurHp = 3000.0f;
	Vector3 ss::PlayerScript::mPoint = Vector3(600.0f, 350.0f, 1.0f);

	PlayerScript::PlayerScript()
		: mCursorPos(Vector3::Zero)
		, mPrevDegree(0.0f)
		, mCollideXaxisCount(0)
		, mCollideYaxisCount(0)
		, mSpellNum(0)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		mState = eState::Idle;
		mDirState = eDirState::Down;

		Animator* at = GetOwner()->GetComponent<Animator>();
		mCursor = new Cursor();

		mIndicator = new Indicator();
		
		//at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);
	}

	void PlayerScript::Update()
	{
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		mPlayerPos = pos;

		SpellWaiting();

		switch (mState)
		{
		case ss::PlayerScript::eState::Idle:
			Idle();
			break;
		case ss::PlayerScript::eState::Move:
			Move();
			break;
		case ss::PlayerScript::eState::ClickMove:
			ClickMove();
			break;
		case ss::PlayerScript::eState::Attack:
			Attack();
			break;
		default:
			break;
		}

		if (Input::GetKeyDown(eKeyCode::P))
		{
			mCurHp -= 500.0f;
		}
	}

	void PlayerScript::Complete()
	{
		int a = 0;
	}

	void PlayerScript::SpellWaiting()
	{
		if (Input::GetKeyDown(eKeyCode::One))
			mSpellNum = 1;
	}

	void PlayerScript::Idle()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::DOWN)
			|| Input::GetKey(eKeyCode::UP)
			|| Input::GetKey(eKeyCode::RIGHT)
			|| Input::GetKey(eKeyCode::LEFT))
			mState = eState::Move;

		Attack();

		ClickMove();

		switch (mDirState)
		{
		case ss::PlayerScript::eDirState::Up:
			animator->PlayAnimation(L"StandUp", true);
			break;
		case ss::PlayerScript::eDirState::Down:
			animator->PlayAnimation(L"StandDown", true);
			break;
		case ss::PlayerScript::eDirState::Left:
			animator->PlayAnimation(L"StandLeft", true);
			break;
		case ss::PlayerScript::eDirState::Right:
			animator->PlayAnimation(L"StandRight", true);
			break;
		default:
			break;
		}
	}

	void PlayerScript::Move()
	{
	/*	if (!(Input::GetKey(eKeyCode::DOWN)
			|| Input::GetKey(eKeyCode::UP)
			|| Input::GetKey(eKeyCode::RIGHT)
			|| Input::GetKey(eKeyCode::LEFT)))
			mState = eState::Idle;*/

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Animator* animator = GetOwner()->GetComponent<Animator>();

		/*if (Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::UP)
			&& !Input::GetKey(eKeyCode::DOWN))
		{
			mDirState = eDirState::Left;
			animator->PlayAnimation(L"MoveLeft", true);
			pos.x -= 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::UP)
			&& !Input::GetKey(eKeyCode::DOWN))
		{
			mDirState = eDirState::Right;
			animator->PlayAnimation(L"MoveRight", true);
			pos.x += 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN)
			&& !Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::UP)
			&& !Input::GetKey(eKeyCode::RIGHT))
		{
			mDirState = eDirState::Down;
			animator->PlayAnimation(L"MoveDown", true);
			pos.y -= 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::UP)
			&& !Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::DOWN))
		{
			mDirState = eDirState::Up;
			animator->PlayAnimation(L"MoveUp", true);
			pos.y += 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::UP) && Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::DOWN))
		{
			mDirState = eDirState::Up;
			animator->PlayAnimation(L"MoveUp", true);
			pos.y += 2.0f * Time::DeltaTime();
			pos.x += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::UP) && Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::DOWN))
		{
			mDirState = eDirState::Up;
			animator->PlayAnimation(L"MoveUp", true);
			pos.y += 2.0f * Time::DeltaTime();
			pos.x -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN) && Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::UP))
		{
			mDirState = eDirState::Down;
			animator->PlayAnimation(L"MoveDown", true);
			pos.y -= 2.0f * Time::DeltaTime();
			pos.x += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN) && Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::UP))
		{
			mDirState = eDirState::Down;
			animator->PlayAnimation(L"MoveDown", true);
			pos.y -= 2.0f * Time::DeltaTime();
			pos.x -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}*/
	}

	void PlayerScript::ClickMove()
	{
		Attack();

		if (Input::GetKey(eKeyCode::RBUTTON))
		{
			mState = eState::ClickMove;
			mIsMoving = true;
			mCursorPos = mCursor->GetPos();
			mCursorPos += Vector3(-0.1f, 0.1f, 0.0f);
			Vector3 playerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			float CurDegree = CalculateMoveDegree(playerPos, mCursorPos);
			float difference = abs(CurDegree - mPrevDegree);

			mCursorProjPos = mCursor->GetProjPos();
			mCursorProjPos.z = 1.0f;
			mPlayerProjPos = Project(playerPos);
			mPlayerProjPos.z = 1.0f;

			if(difference > 90.0f && difference < 270.0f)
				mIsColliding = false;

			mPrevDegree = CurDegree;

			mIndicator->setPos(mCursorPos);
			mIndicator->aniPlay();
		}

		if (!mIsMoving)
			return;
		
		mPlayerPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		MoveToPointAni(mPlayerPos, mCursorPos);
		MoveToPoint(mPlayerPos, mCursorPos);
	}

	void PlayerScript::Attack()
	{
		if (Input::GetKey(eKeyCode::LBUTTON))
		{
			mState = eState::Attack;
			mIsAttacking = true;
			mIsMoving = false;
			mCursorPos = mCursor->GetPos();
			mCursorPos += Vector3(-0.1f, 0.1f, 0.0f);
			mPlayerPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		}

		if (!mIsAttacking)
			return;
		
		if (!mShootOnce && mSpellNum == 0)
		{
			AttackFireBall(mPlayerPos, mCursorPos);
			mShootOnce = true;
		}
		else if (!mShootOnce && mSpellNum == 1)
		{
			ShootMeteor(mCursorPos);
			mShootOnce = true;
			mSpellNum = 0;
		}
		
		AttackAni(mPlayerPos, mCursorPos);
	}

	void PlayerScript::MoveToPoint(Vector3 playerpos, Vector3 point)
	{
		mPoint = point;
		if (playerpos.x < point.x)
			playerpos.x += mSpeed * Time::DeltaTime();
		else if(playerpos.x > point.x)
			playerpos.x -= mSpeed * Time::DeltaTime();

		if (playerpos.y < point.y)
			playerpos.y += mSpeed * Time::DeltaTime();
		else if (playerpos.y > point.y)
			playerpos.y -= mSpeed * Time::DeltaTime();

		if (mIsColliding)
			playerpos = ReverseMove(playerpos, point);

		//playerpos = UnProject(playerpos);
		SetPlayerPos(playerpos);
		GetOwner()->GetComponent<Transform>()->SetPosition(playerpos);

		if (abs(playerpos.x - point.x) <0.001f && abs(playerpos.y - point.y) < 0.001f && mIsColliding == false)
		{
			mState = eState::Idle;
			mIsMoving = false;
		}
	}

	void PlayerScript::MoveToPointAni(Vector3 playerpos, Vector3 point)
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		float degree = math::CalculateDegree(Vector2(playerpos.x, playerpos.y), Vector2(point.x, point.y));

		if (-135.0f <= degree && degree < -45.0f)
		{
			animator->PlayAnimation(L"MoveDown", true);
			mDirState = eDirState::Down;
		}
		else if (45.0f <= degree && degree < 135.0f)
		{
			animator->PlayAnimation(L"MoveUp", true);
			mDirState = eDirState::Up;
		}
		else if (-45.0f <= degree && degree < 45.0f)
		{
			animator->PlayAnimation(L"MoveRight", true);
			mDirState = eDirState::Right;
		}
		else if (135.0f <= degree || degree < -135.0f)
		{
			animator->PlayAnimation(L"MoveLeft", true);
			mDirState = eDirState::Left;
		}

	}

	void PlayerScript::AttackAni(Vector3 playerpos, Vector3 point)
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		float degree = math::CalculateDegree(Vector2(playerpos.x, playerpos.y), Vector2(point.x, point.y));

		if (-135.0f <= degree && degree < -45.0f)
		{
			animator->PlayAnimation(L"AttackDown", true);
			mDirState = eDirState::Down;
		}
		else if (45.0f <= degree && degree < 135.0f)
		{
			animator->PlayAnimation(L"AttackUp", true);
			mDirState = eDirState::Up;
		}
		else if (-45.0f <= degree && degree < 45.0f)
		{
			animator->PlayAnimation(L"AttackRight", true);
			mDirState = eDirState::Right;
		}
		else if (135.0f <= degree || degree < -135.0f)
		{
			animator->PlayAnimation(L"AttackLeft", true);
			mDirState = eDirState::Left;
		}
		

		if (animator->GetActiveAnimation()->IsComplete())
		{
			mState = eState::Idle;
			mIsAttacking = false;
			mShootOnce = false;
		}
	}

	void PlayerScript::AttackFireBall(Vector3 playerpos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(playerpos.x, playerpos.y), Vector2(point.x, point.y));
		FireBall* fireBall = new FireBall(degree);
		fireBall->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, fireBall);
	}

	Vector3 PlayerScript::ReverseMove(Vector3 playerpos, Vector3 point)
	{
		if (mState != eState::ClickMove)
			return playerpos;

		if (mCollideYaxisCount > 0)
		{
			if (playerpos.x < point.x)
				playerpos.x -= (mSpeed + 0.f) * Time::DeltaTime();
			else if (playerpos.x > point.x)
				playerpos.x += (mSpeed + 0.f) * Time::DeltaTime();
		}
		
		if (mCollideXaxisCount > 0)
		{
			if (playerpos.y < point.y)
				playerpos.y -= (mSpeed + 0.f) * Time::DeltaTime();
			else if (playerpos.y > point.y)
				playerpos.y += (mSpeed + 0.f) * Time::DeltaTime();
		}

		return playerpos;
	}

	float PlayerScript::CalculateMoveDegree(Vector3 playerpos, Vector3 point)
	{
		float degree = math::CalculateDegree(Vector2(playerpos.x, playerpos.y), Vector2(point.x, point.y));

		return degree;
	}

	Vector3 PlayerScript::Project(Vector3 pos)
	{
		Viewport viewport;
		viewport.width = 1200.0f;
		viewport.height = 700.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		pos = viewport.Project(pos, Camera::GetGpuProjectionMatrix()
			, Camera::GetGpuViewMatrix(), Matrix::Identity);

		return pos;
	}

	Vector3 PlayerScript::UnProject(Vector3 pos)
	{
		Viewport viewport;
		viewport.width = 1200.0f;
		viewport.height = 700.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		pos = viewport.Unproject(pos, Camera::GetGpuProjectionMatrix()
			, Camera::GetGpuViewMatrix(), Matrix::Identity);

		return pos;
	}

	void PlayerScript::ShootMeteor(Vector3 cursorPos)
	{
		Meteor* meteor = new Meteor();
		meteor->GetComponent<Transform>()->SetPosition(cursorPos);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, meteor);
	}

	void PlayerScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::NormalMonster)
		{
			mIsColliding = true;
			mColliderPos = other->GetOwner()->GetComponent<Transform>()->GetPosition();

			float degree = math::CalculateDegree(Vector2(mPlayerPos.x, mPlayerPos.y)
				, Vector2(mColliderPos.x, mColliderPos.y));

			if ((-60.0f <= degree && degree < 60.0f) || (120.0f <= degree || degree < -120.0f))
			{
				mCollideYaxisCount++;
				other->SetAxisX(false);
			}
			else
			{
				mCollideXaxisCount++;
				other->SetAxisX(true);
			}
		}
	}

	void PlayerScript::OnCollisionStay(Collider2D* other)
	{
		
	}

	void PlayerScript::OnCollisionExit(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::NormalMonster)
		{
			mIsColliding = false;

			if (other->GetAxisX())
				mCollideXaxisCount--;
			else
				mCollideYaxisCount--;
		}
	}

	
}