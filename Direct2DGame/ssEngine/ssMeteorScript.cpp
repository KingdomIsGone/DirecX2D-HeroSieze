#include "ssMeteorScript.h"
#include "ssGameObject.h"

namespace ss
{
	MeteorScript::MeteorScript()
		: mDamage(2000.0f)
	{
	}
	MeteorScript::~MeteorScript()
	{
	}
	void MeteorScript::Initialize()
	{
	}
	void MeteorScript::Update()
	{
	}
	void MeteorScript::OnCollisionEnter(Collider2D* other)
	{
		
	}
	void MeteorScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::NormalMonster)
		{
			if (!mDamageActivate)
				return;
			
			UINT colID = other->GetColliderID();
			for (UINT id : mColIDs)
			{
				if (colID == id)
					return;
			}

			mColIDs.push_back(other->GetColliderID());
			
			other->GetOwner()->SetChangeHpValue(-mDamage);
		}
	}
	void MeteorScript::OnCollisionExit(Collider2D* other)
	{
	}
}
