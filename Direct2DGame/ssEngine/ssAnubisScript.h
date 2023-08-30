#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class AnubisScript : public Script
	{
	public:
		enum class eState
		{
			Dead,
			Sleep,
			Idle,
			ChargedBolt,
			ChargedBoltTwin,
			ChainLight,
			CreateSarco,
		};
	
		AnubisScript();
		~AnubisScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void Awake();
		void Idle();
		void Dead();

		void ChargedBolts(bool isVertical);
		void ChargedTwinBolts();
		void ChainLights();
		void ChainLightsTrifle();
		void CreateSarco();

		void ChangeHP(float value); 
		float GetHP() { return mHp; }
		void DamageCheck();

		void PlayIdleAni() { mAnimator->PlayAnimation(L"Anubis_Down", true); }

		void SetBossHpFill(BossHpFill* fill) { mBossHpFill = fill; }
		void SetImmuneText(ImmuneText* text) { mText = text; }

		static void SarcoDefeat() { mSarcoCount--; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		eState mState;

		float mHp;
		float mSpeed;
		float mAgroDistance;

		Vector3 mPos;
		Vector3 mPlayerPos;

		Vector3 mChainPos[12];
		float mChainTime;
		UINT mChainStage;
		UINT mChainCount;

		bool mXAccess;
		bool mYAccess;
		bool mIsColliding;

		UINT mPatternCount;
		float mPatternTime;

		static UINT mSarcoCount;
		bool mbImmune;

		class Animator* mAnimator;
		class BossHpFill* mBossHpFill;
		class ImmuneText* mText;
	};
}
