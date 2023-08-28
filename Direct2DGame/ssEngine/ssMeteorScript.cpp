#include "ssMeteorScript.h"
#include "ssGameObject.h"
#include "ssPlayerScript.h"
#include "ssAnubisScript.h"
#include "ssMummyScript.h"
#include "ssSkeletonScript.h"


namespace ss
{
	MeteorScript::MeteorScript()
		: mDamage(500.0f)
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
			
			if (other->GetOwner()->GetName() == L"Anubis")
				other->GetOwner()->GetComponent<AnubisScript>()->ChangeHP(-mDamage);
			else if(other->GetOwner()->GetName() == L"Mummy")
				other->GetOwner()->GetComponent<MummyScript>()->ChangeHP(-mDamage);
			else if (other->GetOwner()->GetName() == L"Skeleton")
				other->GetOwner()->GetComponent<SkeletonScript>()->ChangeHP(-mDamage);
		}
	}
	void MeteorScript::OnCollisionExit(Collider2D* other)
	{
	}
}
