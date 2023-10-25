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
			TelePort,
		};

		enum class eDirState
		{
			Up,
			Down,
			Left,
			Right,
		};

		void ExpCheck();
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
		void CalDirState(float degree);

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
		void TelePortCast(Vector3 cursorPos);

		void MpRecovery();
		void HpRecovery();

		void SetInventory(class Inventory* inven) { mInventory = inven; }
		void SetDim(class Dim* dim) { mDim = dim; }
		void SetTree(class SkillTree* tree) { mTree = tree; }

		void PushBackSkillSlot(class SkillSlot* slot) { mSkillSlots.push_back(slot); }
		void SetSkillBox(class SkillSelectBox* box) { mBox = box; }
		void SetLvEffector(class LvUpEffector* effector) { mLvEffector = effector; }
		static void AddExp(float exp) { mExp += exp; }

		static void SetOnOff(bool is) { mbOn = is; }
		void SetStop() { mCursorPos = mPlayerPos; }

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
		bool mRecoveryOn;
		
		class Cursor* mCursor;
		class Indicator* mIndicator;
		class Inventory* mInventory;
		class Dim* mDim;
		class SkillSelectBox* mBox;
		class SkillTree* mTree;
		class LvUpEffector* mLvEffector;

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
		UINT mTeleportSlotNum;

		UINT mTeleportStage;

		std::map<UINT, UINT> mColDirMap;
		std::vector<class SkillSlot*> mSkillSlots;

		static bool mbOn;
		static float mExp;
		static UINT mLevel;
		
		class AudioSource* mAs;
		
	};
}