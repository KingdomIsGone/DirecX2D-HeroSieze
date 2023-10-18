#include "ssFlameScript.h"
#include "ssGameObject.h"
#include "ssTime.h"

namespace ss
{
	FlameScript::FlameScript()
		: mDamage(60.0f)
		, mTime(2.0f)
	{
	}
	FlameScript::~FlameScript()
	{
	}
	void FlameScript::Initialize()
	{
	}
	void FlameScript::Update()
	{
	}
	void FlameScript::OnCollisionEnter(Collider2D* other)
	{

	}
	void FlameScript::OnCollisionStay(Collider2D* other)
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
	void FlameScript::OnCollisionExit(Collider2D* other)
	{
	}
}
