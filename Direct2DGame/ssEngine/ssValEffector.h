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

		void SetValkyrie(class Valkyrie* valk) { mValk = valk; }
		void SetOffset(Vector3 offset) { mOffset = offset; }
		void PlayNormalRushEffect(e4Direction dir);

	private:
		Transform* mTransform;
		Vector3 mPos;
		Vector3 mOffset;
		Vector3 mValkPos;

		class Valkyrie* mValk;
		class ValkyrieScript* mScript;
		class Animator* mAnimator;

	};
}