#include "ssFireballScript.h"
#include "ssGameObject.h"
#include "ssSkeletonScript.h"
#include "ssMummyScript.h"
#include "ssSarcophagus.h"

namespace ss
{
	FireBallScript::FireBallScript()
		: mDamage(200.0f)
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
			if (other->GetOwner()->GetName() == L"Skeleton")
				other->GetOwner()->GetComponent<SkeletonScript>()->ChangeHP(-mDamage);
			else if (other->GetOwner()->GetName() == L"Mummy")
				other->GetOwner()->GetComponent<MummyScript>()->ChangeHP(-mDamage);
			else if (other->GetOwner()->GetName() == L"Sarcophagus")
				dynamic_cast<Sarcophagus*>(other->GetOwner())->ChangeHp(-mDamage);
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