#include "ssMagicBallScript.h"
#include "ssGameObject.h"
#include "ssPlayerScript.h"

namespace ss
{
	MagicBallScript::MagicBallScript()
		: mDamage(100.0f)
	{
	}
	MagicBallScript::~MagicBallScript()
	{
	}
	void MagicBallScript::Initialize()
	{
	}
	void MagicBallScript::Update()
	{
	}

	void MagicBallScript::OnCollisionEnter(Collider2D* other)
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

	void MagicBallScript::OnCollisionStay(Collider2D* other)
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

	void MagicBallScript::OnCollisionExit(Collider2D* other)
	{
	}
}