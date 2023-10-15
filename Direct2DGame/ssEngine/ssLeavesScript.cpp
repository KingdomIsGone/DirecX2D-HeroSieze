#include "ssLeavesScript.h"
#include "ssCollider2D.h"
#include "ssLeaves01.h"

namespace ss
{
	LeavesScript::LeavesScript()
	{
	}
	LeavesScript::~LeavesScript()
	{
	}
	void LeavesScript::Initialize()
	{
	}
	void LeavesScript::Update()
	{
	}

	void LeavesScript::OnCollisionEnter(Collider2D* other)
	{

	}

	void LeavesScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			mObj->BindCB(0.5f);
		}

		
	}

	void LeavesScript::OnCollisionExit(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			mObj->BindCB(1.f);
		}
	}
}