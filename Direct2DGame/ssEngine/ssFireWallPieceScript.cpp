#include "ssFireWallPieceScript.h"
#include "ssGameObject.h"
#include "ssTime.h"


namespace ss
{
	FireWallPieceScript::FireWallPieceScript()
		: mDamage(80.0f)
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

			if (mTime > 0.3f)
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

			other->GetOwner()->SetChangeHpValue(-mDamage);
		}
	}
	void FireWallPieceScript::OnCollisionExit(Collider2D* other)
	{
	}
}
