#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class BigLightningScript : public Script
	{
	public:
		BigLightningScript();
		~BigLightningScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetDamageApply(bool is) { mDamageApply = is; }

	private:
		Vector3 mPos;
		Vector3 mPlayerPos;
		bool mDamageOnce;
		bool mDamageApply;
		class Animator* mAnimator;
		
		
	};
}
