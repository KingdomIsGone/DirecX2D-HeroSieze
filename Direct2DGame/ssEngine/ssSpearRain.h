#pragma once
#include "ssGameObject.h"

namespace ss
{
	class SpearRain : public GameObject
	{
	public:
		SpearRain();
		~SpearRain();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		
		void MakeShadow();
		bool GetAniComplete() { return mAniComplete; }

		void BindCB(float alpha);

	private:
		Transform* mTransform;
		Vector3 mPos;
		float mSpeed;
		float mShadowScale;
		bool mDeadSign;

		class Collider2D* mCollider;
		class Animator* mAnimator;
		class MeshRenderer* mr;
		class AudioSource* mAs;


		UINT mStage;
		bool mAniComplete;

	};
}
