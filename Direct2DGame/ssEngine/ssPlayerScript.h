#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class Collider2D;
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class eState
		{
			Idle,
			Move,
			ClickMove,
			Attack,
			Sleep,
		};

		enum class eDirState
		{
			Up,
			Down,
			Left,
			Right,
		};

		void Complete();
		void SpellWaiting();

		void Idle();
		void Move();
		void ClickMove();
		void Attack();
		void Sleep();

		void MoveToPoint(Vector3 playerpos, Vector3 point);
		void MoveToPointAni(Vector3 playerpos, Vector3 point);

		void AttackAni(Vector3 playerpos, Vector3 point);
		void AttackFireBall(Vector3 playerpos, Vector3 point);

		Vector3 ReverseMove(Vector3 playerpos, Vector3 point);
		float CalculateMoveDegree(Vector3 playerpos, Vector3 point);

		Vector3 Project(Vector3 pos);
		Vector3 UnProject(Vector3 pos);

		float GetHp() { return mCurHp; }
		float GetMp() { return mCurMp; }
		static void ChangeHp(float value) { mCurHp += value; }

		static Vector3 GetPlayerPos() { return mPlayerPos; }
		static void SetPlayerPos(Vector3 pos) { mPlayerPos = pos; }
		static float GetPlayerSpeed() { return mSpeed; }
		static Vector3 GetPoint() { return mPoint; }
		static UINT GetSpellNum() { return mSpellNum; }

		void ShootMeteor(Vector3 cursorPos);
		void FireWalls(Vector3 cursorPos);
		void FireAuraCast();
		void HydraCast(Vector3 cursorPos);

		void MpRecovery();

		void SetInventory(class Inventory* inven) { mInventory = inven; }

		void PushBackSkillSlot(class SkillSlot* slot) { mSkillSlots.push_back(slot); }

	private:
		static Vector3 mPlayerPos;
		static Vector3 mPoint;
		static float mSpeed;
		Vector3 mPlayerProjPos;
		Transform* mTransform;

		eState mState;
		eDirState mDirState;

		static float mCurHp;
		static float mCurMp;
		float mFullMp;
		
		class Cursor* mCursor;
		class Indicator* mIndicator;
		class Inventory* mInventory;

		bool mIsMoving;
		bool mIsAttacking;
		bool mShootOnce;
		bool mIsColliding;
		UINT mCollideXaxisCount;
		UINT mCollideYaxisCount;

		UINT mTopColCount;
		UINT mBottomColCount;
		UINT mRightColCount;
		UINT mLeftColCount;

		Vector3 mCursorPos;
		Vector3 mCursorProjPos;
		float mPrevDegree;
		Vector3 mColliderPos;

		static UINT mSpellNum;

		std::map<UINT, UINT> mColDirMap;
		std::vector<class SkillSlot*> mSkillSlots;
	};
}