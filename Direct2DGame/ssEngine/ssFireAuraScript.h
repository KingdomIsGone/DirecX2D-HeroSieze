#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class FireAuraScript : public Script
	{
	public:
		FireAuraScript();
		~FireAuraScript();

		virtual void Initialize() override;
		virtual void Update() override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		float mDamage;
		float mTime;

		std::vector<UINT> mColIDs;

	};
}