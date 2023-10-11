#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Valkyrie : public GameObject
	{
	public:
		Valkyrie();
		~Valkyrie();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		//ani
		void PlayTransformAni();

	private:
		Transform* mTransform;
		Vector3 mPos;

		class ValkyrieScript* mScript;
		class Animator* mAnimator;

		UINT mTransformAniStage;

		float mPrevHp;
		float mCurHp;

	};
}