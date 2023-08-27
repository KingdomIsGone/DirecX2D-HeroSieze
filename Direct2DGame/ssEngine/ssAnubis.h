#pragma once
#include "ssGameObject.h"

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

	private:
		Transform* mTransform;
		Vector3 mPos;

		class SkeletonScript* mMScript;
		class EnemyHpBar* mHpBar;
		class EnemyHpBarFill* mHpBarFill;
		class Animator* mAnimator;
		class Collider2D* mCollider;

		float mPrevHp;
		float mCurHp;
	};
}
