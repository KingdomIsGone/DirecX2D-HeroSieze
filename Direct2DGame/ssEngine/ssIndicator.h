#pragma once
#include "ssGameObject.h"

namespace ss
{
	static class Indicator : public GameObject
	{
	public:
		Indicator();
		~Indicator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void aniPlay();
		void setPos(Vector3 pos) { mPos = pos; }

	private:
		Transform* mTransform;
		static Vector3 mPos;
		float mSpeed;

		static class Animator* mAnimator;
	};
}