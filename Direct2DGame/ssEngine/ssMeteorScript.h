#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class MeteorScript : public Script
	{
	public:
		MeteorScript();
		~MeteorScript();

		virtual void Initialize() override;
		virtual void Update() override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetDamageActivate() { mDamageActivate = true; }

	private:
		float mDamage;
		bool mDamageActivate;

		std::vector<UINT> mColIDs;
		
	};
}