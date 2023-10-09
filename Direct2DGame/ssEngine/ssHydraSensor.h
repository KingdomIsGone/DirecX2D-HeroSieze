#pragma once
#include "ssGameObject.h"

namespace ss
{
	class HydraSensor : public GameObject
	{
	public:
		HydraSensor();
		~HydraSensor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetHydra(class Hydra* hydra) { mHydra = hydra; }
		class HydraScript* GetScript() { return mScript; }

		

		

	private:
		Transform* mTransform;
		Vector3 mPos;

		float mDamage;


		class Animator* mAnimator;
		class Collider2D* mCollider;
		class Hydra* mHydra;
		class HydraScript* mScript;
	};
}