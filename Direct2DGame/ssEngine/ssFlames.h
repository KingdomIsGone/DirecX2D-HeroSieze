#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Flames : public GameObject
	{
	public:
		Flames();
		~Flames();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Transform* mTransform;
		Vector3 mPos;

		float mDamage;
		float mDeadTime;

		class FlameScript* mScript;
		class Animator* mAnimator;
	};
}