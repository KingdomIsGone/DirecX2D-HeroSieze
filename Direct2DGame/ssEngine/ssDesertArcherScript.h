#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class DesertArcherScript : public Script
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
		DesertArcherScript();
		~DesertArcherScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void Idle();
		void Chase();
		void Attack();

		void PlayMoveAni();

		void CalDir(Vector3 targetPos);
		Vector3 ReverseMove();
		float CalculateMoveDegree(Vector3 monsterpos, Vector3 point);
		void ColideClear();

		float GetHP() { return mHp; }

		void DamageCheck();

		void SetItemHave(UINT num) { mItemHave = num; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		eState mState;
		eDirState mDirState;
		UINT mItemHave;

		float mHp;
		float mSpeed;
		float mAgroDistance;

		Vector3 mPos;
		Vector3 mPlayerPos;

		bool mXAccess;
		bool mYAccess;
		bool mIsColliding;

		class Animator* mAnimator;
		class Collider2D* mCollider;
		class AudioSource* mAs;

		
		std::map<UINT, UINT> mColDirMap;
		std::map<UINT, Collider2D*> mColAdressMap;
	};
}