#include "ssFireballScript.h"
#include "ssGameObject.h"
#include "ssMonsterHpScript.h"

namespace ss
{
	FireBallScript::FireBallScript()
		: mDamage(500.0f)
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
		
	}

	void FireBallScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::NormalMonster)
		{
			other->GetOwner()->GetComponent<MonsterHpScript>()->ModifyHp(-mDamage);
		}

		if (other->GetCollideType() != eCollideType::Player)
		{
			GetOwner()->SetState(GameObject::eState::Dead);
		}
	}

	void FireBallScript::OnCollisionExit(Collider2D* other)
	{
	}
}