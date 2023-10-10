#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ValEffector : public GameObject
	{
	public:
		ValEffector();
		~ValEffector();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindCB(float Radd, float Gadd, float Badd, float A);

	private:
		Transform* mTransform;
		Vector3 mPos;

		class ValkyrieScript* mScript;
		class Animator* mAnimator;

	};
}