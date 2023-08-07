#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class MonsterScript : public Script
	{
	public:
		enum class eState
		{
			Idle,
			Chase,
			Attack,
		};

		enum class eDirState
		{
			Up,
			Down,
			Left,
			Right,
		};
		MonsterScript();
		~MonsterScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void Idle();
		void Chase();
		void Attack();

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		eState mState;
		eDirState mDirState;
	
	};
}