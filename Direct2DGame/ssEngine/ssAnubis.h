#pragma once
#include "ssGameObject.h"
#include "ssBossHpFill.h"

namespace ss
{
	class Anubis : public GameObject
	{
	public:
		Anubis();
		~Anubis();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Sleep();

		bool GetAwake() { return mbAwake; }
		bool GetDead() { return mbDead; }
		void SetDead() { mbDead = true; }

		void SetBossHpFill(BossHpFill* fill);

	private:
		Transform* mTransform;
		Vector3 mPos;

		class BossHpBar* mHpBar;
		class EnemyHpBarFill* mHpBarFill;
		class Animator* mAnimator;
		class Collider2D* mCollider;
		class ImmuneText* mText;

		float mPrevHp;
		float mCurHp;

		bool mbAwake;
		bool mbDead;

		class AnubisScript* mScript;
	};
}
