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

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;
		


	private:
		eState mState;
		eDirState mDirState;
		
		class Cursor* mCursor;
		class Indicator* mIndicator;

		bool mIsMoving;
		bool mIsAttacking;
		bool mShootOnce;
		bool mIsColliding;
		Vector3 mCursorPos;
		Vector3 mPlayerPos;
		float mSpeed;
		float mPrevDegree;

	};
}