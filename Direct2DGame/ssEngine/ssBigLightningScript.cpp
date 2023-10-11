#include "ssBigLightningScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"
#include "ssSceneManager.h"
#include < time.h >
#include "ssAnimator.h"
#include "ssPlayer.h"

namespace ss
{
	BigLightningScript::BigLightningScript()
	{
	}
	BigLightningScript::~BigLightningScript()
	{
	}
	void BigLightningScript::Initialize()
	{
		
	}

	void BigLightningScript::Update()
	{
		
	}


	void BigLightningScript::OnCollisionEnter(Collider2D* other)
	{
		
	}
	void BigLightningScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player
			&& !mDamageOnce && mDamageApply)
		{
			dynamic_cast<Player*>(other->GetOwner())->GetScript()->ChangeHp(-500.f);
			mDamageOnce = true;
		}
	}
	void BigLightningScript::OnCollisionExit(Collider2D* other)
	{
	}
}