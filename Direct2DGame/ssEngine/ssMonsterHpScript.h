#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class MonsterHpScript : public Script
	{
	public:
		MonsterHpScript();
		~MonsterHpScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void ModifyHp(float modifier) { mHp += modifier; }
		float GetHp() { return mHp; }

	private:
		float mHp;
	};
}