#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class TreeMonScript : public Script
	{
	public:
		enum class eState
		{
			Idle,
			Chase,
			Attack,
			Dead,
		};

		enum class eDirState
		{
			Up,
			Down,
			Left,
			Right,
		};
		TreeMonScript();
		~TreeMonScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void Idle();
		void Chase();
		void Attack();

		void PlayMoveAni();

		void CalDir(Vector3 targetPos);
		Vector3 ReverseMove();
		float CalculateMoveDegree(Vector3 monsterpos, Vector3 point);

		float GetHP() { return mHp; }

		void DamageCheck();

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		eState mState;
		eDirState mDirState;

		float mHp;
		float mSpeed;
		float mAgroDistance;

		Vector3 mPos;
		Vector3 mPlayerPos;

		bool mXAccess;
		bool mYAccess;
		bool mIsColliding;

		class Animator* mAnimator;

		UINT mTopColCount;
		UINT mBottomColCount;
		UINT mRightColCount;
		UINT mLeftColCount;
		std::map<UINT, UINT> mColDirMap;
	};
}