#include "ssPlayerScript.h"
#include "ssCameraScript.h"
#include "ssTransform.h"
#include "ssGameObject.h"
#include "ssTime.h"
#include "ssInput.h"
#include "ssAnimator.h"
#include "ssResources.h"
#include "ssMeshRenderer.h"

namespace ss
{
	PlayerScript::PlayerScript()
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		Animator* at = GetOwner()->GetComponent<Animator>();

		//at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);
	}

	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Animator* animator = GetOwner()->GetComponent<Animator>();


		if (Input::GetKey(eKeyCode::LEFT) 
			&& !Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::UP)
			&& !Input::GetKey(eKeyCode::DOWN))
		{
			animator->PlayAnimation(L"MoveLeft", true);
			pos.x -= 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT) 
			&& !Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::UP)
			&& !Input::GetKey(eKeyCode::DOWN))
		{
			animator->PlayAnimation(L"MoveRight", true);
			pos.x += 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN)
			&& !Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::UP)
			&& !Input::GetKey(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"MoveDown", true);
			pos.y -= 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::UP)
			&& !Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::DOWN))
		{
			animator->PlayAnimation(L"MoveUp", true);
			pos.y += 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::UP) && Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::DOWN))
		{
			animator->PlayAnimation(L"MoveUp", true);
			pos.y += 2.0f * Time::DeltaTime();
			pos.x += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::UP) && Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::DOWN))
		{
			animator->PlayAnimation(L"MoveUp", true);
			pos.y += 2.0f * Time::DeltaTime();
			pos.x -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN) && Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::UP))
		{
			animator->PlayAnimation(L"MoveDown", true);
			pos.y -= 2.0f * Time::DeltaTime();
			pos.x += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN) && Input::GetKey(eKeyCode::LEFT)
			&& !Input::GetKey(eKeyCode::RIGHT)
			&& !Input::GetKey(eKeyCode::UP))
		{
			animator->PlayAnimation(L"MoveDown", true);
			pos.y -= 2.0f * Time::DeltaTime();
			pos.x -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

	}

	void PlayerScript::Complete()
	{
		int a = 0;
	}
}