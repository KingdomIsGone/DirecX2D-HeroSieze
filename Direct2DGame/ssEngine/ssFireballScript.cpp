#include "ssFireballScript.h"
#include "ssGameObject.h"

namespace ss
{
	FireBallScript::FireBallScript()
		: mDamage(100.0f)
	{
	}
	FireBallScript::~FireBallScript()
	{
	}
	void FireBallScript::Initialize()
	{
	}
	void FireBallScript::Update()
	{
	}

	void FireBallScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::NormalMonster)
		{
			if (!mOnce)
			{
				other->GetOwner()->SetChangeHpValue(-mDamage);
				mCount = 0;
				mOnce = true;
			}
		}
	}

	void FireBallScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Wall)
		{
			GetOwner()->SetState(GameObject::eState::Dead);
		}
		else if (other->GetCollideType() == eCollideType::NormalMonster)
		{
			mCount++;

			if(mCount > 3)
				GetOwner()->SetState(GameObject::eState::Dead);
		}
	}

	void FireBallScript::OnCollisionExit(Collider2D* other)
	{
	}
}