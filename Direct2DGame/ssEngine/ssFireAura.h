#pragma once
#include "ssGameObject.h"

namespace ss
{
	class FireAura : public GameObject
	{
	public:
		FireAura();
		~FireAura();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Transform* mTransform;
		Vector3 mPos;

		float mDamage;
		float mDuration;
		UINT mStage;

		class FireAuraScript* mMScript;
		class Animator* mAnimator;
	};
}