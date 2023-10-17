#include "ssArrowScript.h"
#include "ssGameObject.h"
#include "ssPlayerScript.h"

namespace ss
{
	ArrowScript::ArrowScript()
		: mDamage(100.0f)
	{
	}
	ArrowScript::~ArrowScript()
	{
	}
	void ArrowScript::Initialize()
	{
	}
	void ArrowScript::Update()
	{
	}

	void ArrowScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			if (!mOnce)
			{
				PlayerScript::ChangeHp(-mDamage);
				mCount = 0;
				mOnce = true;
			}
		}
	}

	void ArrowScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Wall)
		{
			GetOwner()->SetState(GameObject::eState::Dead);
		}
		else if (other->GetCollideType() == eCollideType::Player)
		{
			mCount++;

			if (mCount > 5)
				GetOwner()->SetState(GameObject::eState::Dead);
		}
	}

	void ArrowScript::OnCollisionExit(Collider2D* other)
	{
	}
}