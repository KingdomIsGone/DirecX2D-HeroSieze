#pragma once
#include "ssGameObject.h"

namespace ss
{
	class BigLightning : public GameObject
	{
	public:
		BigLightning();
		~BigLightning();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindCB(float Radd, float Gadd, float Badd, float A);

		void SetOffset(Vector3 offset) { mOffset = offset; }
		void PlayAni();
		void SetPosition(Vector3 pos) { mPos = pos; }
		UINT GetStage() { return mStage; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		Vector3 mOffset;
		Vector3 mValkPos;

		UINT mStage;

		class Animator* mAnimator;
		class Collider2D* mCollider;
		class BigLightningScript* mScript;

		float mRotation;

	};
}