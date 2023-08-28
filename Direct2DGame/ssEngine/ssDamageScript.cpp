#include "ssDamageScript.h"
#include "ssGameObject.h"
#include "ssPlayerScript.h"
#include "ssChargedBolt.h"
#include "ssChainLightening.h"

namespace ss
{
	DamageScript::DamageScript()
	{
	}
	DamageScript::~DamageScript()
	{
	}
	void DamageScript::Initialize()
	{
	}
	void DamageScript::Update()
	{
	}
	void DamageScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			float Damage;
			if (GetOwner()->GetName() == L"ChargedBolt")
			{
				Damage = ChargedBolt::GetDamage();
			}
			else if (GetOwner()->GetName() == L"ChainLightening")
				Damage = ChainLightening::GetDamage();

			other->GetOwner()->GetComponent<PlayerScript>()->ChangeHp(-Damage);

			GetOwner()->SetState(GameObject::eState::Dead);
		}
		else if (other->GetCollideType() == eCollideType::NormalMonster)
		{

		}
	}
	void DamageScript::OnCollisionStay(Collider2D* other)
	{
	}
	void DamageScript::OnCollisionExit(Collider2D* other)
	{
	}
}