#pragma once
#include "ssGameObject.h"

namespace ss
{
	class SpearPiece : public GameObject
	{
	public:
		SpearPiece();
		~SpearPiece();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		static float GetDamage() { return mDamage; }

		void BindCB(float alpha);

	private:
		Transform* mTransform;
		Vector3 mPos;
		float mSpeed;
		float mAlpha;
		float mDeleteTime;
		float mMoveDistance;

		class Collider2D* mCollider;
		class AudioSource* mAs;

		static float mDamage;
	};
}
