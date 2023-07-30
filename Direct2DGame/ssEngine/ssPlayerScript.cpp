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

namespace ss
{
	PlayerScript::PlayerScript()
		: mCursorPos(Vector3::Zero)
		, mPlayerPos(Vector3::Zero)
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

		//at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);
		
	}

	void PlayerScript::Update()
	{
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
		default:
			break;
		}

		
	}

	void PlayerScript::Complete()
	{
		int a = 0;
	}

	void PlayerScript::Idle()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::DOWN)
			|| Input::GetKey(eKeyCode::UP)
			|| Input::GetKey(eKeyCode::RIGHT)
			|| Input::GetKey(eKeyCode::LEFT))
			mState = eState::Move;

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
		if (!(Input::GetKey(eKeyCode::DOWN)
			|| Input::GetKey(eKeyCode::UP)
			|| Input::GetKey(eKeyCode::RIGHT)
			|| Input::GetKey(eKeyCode::LEFT)))
			mState = eState::Idle;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::LEFT)
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
		}
	}

	void PlayerScript::ClickMove()
	{
		if (Input::GetKey(eKeyCode::RBUTTON))
		{
			mState = eState::ClickMove;
			mIsMoving = true;
			mCursorPos = mCursor->GetPos();
			mCursorPos += Vector3(-0.1f, 0.1f, 0.0f);
		}

		if (!mIsMoving)
			return;
		
		Vector3 playerPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		MoveToPointAni(playerPos, mCursorPos);
		MoveToPoint(playerPos, mCursorPos);
	}

	void PlayerScript::MoveToPoint(Vector3 playerpos, Vector3 point)
	{
		if (playerpos.x < point.x)
			playerpos.x += 2.0f * Time::DeltaTime();
		else if(playerpos.x > point.x)
			playerpos.x -= 2.0f * Time::DeltaTime();

		if (playerpos.y < point.y)
			playerpos.y += 2.0f * Time::DeltaTime();
		else if (playerpos.y > point.y)
			playerpos.y -= 2.0f * Time::DeltaTime();

		GetOwner()->GetComponent<Transform>()->SetPosition(playerpos);

		if (abs(playerpos.x - point.x) <0.001f && abs(playerpos.y - point.y) < 0.001f)
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
			animator->PlayAnimation(L"MoveDown", true);
		else if(45.0f <= degree && degree < 135.0f)
			animator->PlayAnimation(L"MoveUp", true);
		else if(-45.0f <= degree && degree <45.0f)
			animator->PlayAnimation(L"MoveRight", true);
		else if(135.0f <= degree || degree < -135.0f)
			animator->PlayAnimation(L"MoveLeft", true);
	}
}