#pragma once
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class HydraScript : public Script
	{
	public:
		HydraScript();
		~HydraScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class eDirState
		{
			Down,
			DownLeft,
			DownRight,
			Right,
			Left,
			UpLeft,
			UpRight,
			Up,
		};
		enum class eState
		{
			Idle,
			InEnemy,
			Attack,
		};

		void Idle();
		void InEnemy();
		void Attack();

		void SetHydra(class Hydra* hydra) { mHydra = hydra; }
		void AttackFireBall(Vector3 hydraPos, Vector3 point);
		void CalDir(Vector3 targetPos);
		void PlayAtkAni();
		void PlayStandAni();

	private:
		eState mState;

		float mDamage;
		float mTime;
		Vector3 mHydraPos;
		Vector3 mTargetPos;
		bool mOnAttack;
		eDirState mDirState;
		std::vector<UINT> mColIDs;

		class Hydra* mHydra;
		class Animator* mAnimator;
	};
}