#include "ssFireWallPieceScript.h"
#include "ssGameObject.h"
#include "ssPlayerScript.h"
#include "ssAnubisScript.h"
#include "ssMummyScript.h"
#include "ssSkeletonScript.h"
#include "ssSarcophagus.h"
#include "ssTime.h"


namespace ss
{
	FireWallPieceScript::FireWallPieceScript()
		: mDamage(150.0f)
		, mTime(2.0f)
	{
	}
	FireWallPieceScript::~FireWallPieceScript()
	{
	}
	void FireWallPieceScript::Initialize()
	{
	}
	void FireWallPieceScript::Update()
	{
	}
	void FireWallPieceScript::OnCollisionEnter(Collider2D* other)
	{

	}
	void FireWallPieceScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::NormalMonster)
		{
			mTime += Time::DeltaTime();

			if (mTime > 1.0f)
			{
				mColIDs.clear();
				mTime = 0.0f;
			}
			
			UINT colID = other->GetColliderID();
			for (UINT id : mColIDs)
			{
				if (colID == id)
					return;
			}

			mColIDs.push_back(other->GetColliderID());

			if (other->GetOwner()->GetName() == L"Anubis")
				other->GetOwner()->GetComponent<AnubisScript>()->ChangeHP(-mDamage);
			else if (other->GetOwner()->GetName() == L"Mummy")
				other->GetOwner()->GetComponent<MummyScript>()->ChangeHP(-mDamage);
			else if (other->GetOwner()->GetName() == L"Skeleton")
				other->GetOwner()->GetComponent<SkeletonScript>()->ChangeHP(-mDamage);
			else if (other->GetOwner()->GetName() == L"Sarcophagus")
				dynamic_cast<Sarcophagus*>(other->GetOwner())->ChangeHp(-mDamage);
		}
	}
	void FireWallPieceScript::OnCollisionExit(Collider2D* other)
	{
	}
}
