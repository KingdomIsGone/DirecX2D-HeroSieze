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
			Positioning,
			Chase, 
			LightningRush,
			LightningAssault,
			CloneAssault,
			BigLightning,
			ThrowRightBall,
			SpearRainCast,
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
			Assault,
		};

		ValkyrieScript();
		~ValkyrieScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		void ChangeHP(float value);
		float GetHP() { return mHp; }
		void DamageCheck();
		void CalDir(Vector3 targetPos);
		void ChangeColSetting();

		void Pattern();
		void Pattern2();

		void Positioning();
		void Dead();
		void Chase();
		void WalkAni();
		void PlayTransform();
		void LightningRush();
		void LightningAssault();
		void BigLightningCast();
		void CloneAssaultCast();
		void ThrowLightBall();
		void SpearRainCast();

		void SetBossHpFill(BossHpFill* fill) { mBossHpFill = fill; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetEffector(class ValEffector* effector) { mEffector = effector; }
		void SetValk(class Valkyrie* valk) { mValk = valk; }

	private:
		eState mState;
		eDirState mDirState;
		eColideState mColState;

		float mHp;
		float mSpeed;
		float mAgroDistance;

		Transform* mTransform;
		Vector3 mPos;
		Vector3 mPlayerPos;

		UINT mPatternNum;
		float mPatternTime;
		
		//Transform
		bool mAwake;
		UINT mTransformAniStage;

		//Rush
		UINT mRushStage;
		float mRushReadySpeed;
		float mRushAxisDist;
		Vector3 mRushBeforePos;
		float mRushBackDist;
		float mRushDistRow;
		float mRushDistCol;
		float mRushSpeed;
		bool mRushSoundOnce;

		//Assault
		UINT mEffectCount;

		//Clone Assault
		bool mCloneOnce;
		class CloneAssault* mClone;
		bool mStart;
		bool On;
		bool mAssaultSndOnce;

		//BigLightning
		UINT mBigStage;
		bool mBigOnce;
		class BigLightning* mBig;
		bool mCircleSndOnce;
		
		//ThrowLightBall
		UINT mBallStage;

		//SpearRain
		UINT mRainStage;
		Vector3 mRainTargetPos;
		float mInterval;
		UINT mPieceCount;
		class SpearRain* mRain;
		bool mRainSoundOnce;

		//Dead
		UINT mDeadStage;
		float mAlpha;
		bool mDeathSndOnce;

		Vector3 mCenterPoint;

		class Animator* mAnimator;
		class BossHpFill* mBossHpFill;
		class Collider2D* mCollider;
		class ValEffector* mEffector;
		class Valkyrie* mValk;
		class ValThunderEffect* mThunderEffect;
		class AudioSource* mAs;

	};
}
