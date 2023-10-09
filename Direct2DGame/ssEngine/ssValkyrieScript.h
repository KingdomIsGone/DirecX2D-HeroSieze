#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class ValkyrieScript : public Script
	{
	public:
		enum class eState
		{
			Dead,
			Sleep,
			Transform,
			Chase,
			MeleeAtk,
		
		};
		enum class eDirState
		{
			Up,
			UpRight,
			UpLeft,
			Down,
			DownRight,
			DownLeft,
			Right,
			Left,
		};
		enum class eColideState
		{
			Normal,
			Rush,
		};

		ValkyrieScript();
		~ValkyrieScript();

		virtual void Initialize() override;
		virtual void Update() override;


		void ChangeHP(float value);
		float GetHP() { return mHp; }
		void DamageCheck();
		void CalDir(Vector3 targetPos);
		void ChangeColSetting();

		void Dead();
		void Chase();
		void WalkAni();
		void LightningRush();

		void SetBossHpFill(BossHpFill* fill) { mBossHpFill = fill; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		eState mState;
		eDirState mDirState;
		eColideState mColState;

		float mHp;
		float mSpeed;
		float mAgroDistance;

		Vector3 mPos;
		Vector3 mPlayerPos;

		//Rush
		UINT mRushStage;
		float mRushReadySpeed;
		float mRushAxisDist;
		Vector3 mRushBeforePos;
		float mRushBackDist;
		float mRushDistRow;
		float mRushDistCol;
		float mRushSpeed;


		class Animator* mAnimator;
		class BossHpFill* mBossHpFill;
		class Collider2D* mCollider;
	};
}
