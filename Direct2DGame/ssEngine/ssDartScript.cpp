#include "ssDartScript.h"
#include "ssGameObject.h"
#include "ssPlayerScript.h"

namespace ss
{
	DartScript::DartScript()
		: mDamage(100.0f)
	{
	}
	DartScript::~DartScript()
	{
	}
	void DartScript::Initialize()
	{
	}
	void DartScript::Update()
	{
	}

	void DartScript::OnCollisionEnter(Collider2D* other)
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

	void DartScript::OnCollisionStay(Collider2D* other)
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

	void DartScript::OnCollisionExit(Collider2D* other)
	{
	}
}