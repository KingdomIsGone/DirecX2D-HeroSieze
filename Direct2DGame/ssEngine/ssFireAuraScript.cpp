#include "ssFireAuraScript.h"
#include "ssGameObject.h"
#include "ssTime.h"
#include "ssPlayerScript.h"

namespace ss
{
	FireAuraScript::FireAuraScript()
		: mDamage(100.0f)
		, mTime(0.0f)
	{
	}
	FireAuraScript::~FireAuraScript()
	{
	}
	void FireAuraScript::Initialize()
	{
	}
	void FireAuraScript::Update()
	{
		mTime += 1.f * Time::DeltaTime();

		Vector3 playerPos = PlayerScript::GetPlayerPos();
		playerPos.z += 0.001f;
		GetOwner()->GetComponent<Transform>()->SetPosition(playerPos);
	}
	void FireAuraScript::OnCollisionEnter(Collider2D* other)
	{
		int a = 0;
	}
	void FireAuraScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::NormalMonster)
		{
			if (mTime > 0.5f)
			{
				mColIDs.clear();
				mTime = 0.0f;
			}

			Vector3 targetPos = other->GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 playerPos = PlayerScript::GetPlayerPos();

			if (math::GetDistance(targetPos, playerPos) > 1.2f)
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
	void FireAuraScript::OnCollisionExit(Collider2D* other)
	{
		int a = 0;
	}
}