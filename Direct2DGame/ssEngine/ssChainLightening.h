#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ChainLightening : public GameObject
	{
	public:
		ChainLightening();
		~ChainLightening();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetForInstance(bool is) { mForInstance = is; }
		static float GetDamage() { return mDamage; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		float mSpeed;

		float mDeleteTime;
		bool mForInstance;

		bool mbIsVertical;

		class Collider2D* mCollider;
		class Animator* mAnimator;

		static float mDamage;
	};
}
