#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			ClickMove,
			Attack,
		};
	
		enum class eDirState
		{
			Up,
			Down,
			Left,
			Right,
		};
		PlayerScript();
		~PlayerScript();


		virtual void Initialize() override;
		virtual void Update() override;

		void Complete();

		void Idle();
		void Move();
		void ClickMove();
		void Attack();

		void MoveToPoint(Vector3 playerpos, Vector3 point);
		void MoveToPointAni(Vector3 playerpos, Vector3 point);

		void AttackAni(Vector3 playerpos, Vector3 point);
		void AttackFireBall(Vector3 playerpos, Vector3 point);


		Vector3 ReverseMove(Vector3 playerpos, Vector3 point);
		float CalculateMoveDegree(Vector3 playerpos, Vector3 point);

		Vector3 Project(Vector3 pos);
		Vector3 UnProject(Vector3 pos);

		static Vector3 GetPlayerPos() { return mPlayerPos; }
		static void SetPlayerPos(Vector3 pos) { mPlayerPos = pos; }
		static float GetPlayerSpeed() { return mSpeed; }
		static Vector3 GetPoint() { return mPoint; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
		


	private:
		static Vector3 mPlayerPos;
		static Vector3 mPoint;
		static float mSpeed;
		Vector3 mPlayerProjPos;

		eState mState;
		eDirState mDirState;
		
		class Cursor* mCursor;
		class Indicator* mIndicator;

		bool mIsMoving;
		bool mIsAttacking;
		bool mShootOnce;
		bool mIsColliding;
		UINT mCollideXaxisCount;
		UINT mCollideYaxisCount;

		Vector3 mCursorPos;
		Vector3 mCursorProjPos;
		float mPrevDegree;
		Vector3 mColliderPos;
	};
}