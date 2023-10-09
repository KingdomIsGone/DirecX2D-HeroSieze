#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Hydra : public GameObject
	{
	public:
		Hydra();
		~Hydra();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		

		class Animator* GetAnimator() { return mAnimator; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		float mDamage;
		float mDuration;
		UINT mStage;

		class FireAuraScript* mMScript;
		class Animator* mAnimator;
		class HydraSensor* mSensor;
	};
}