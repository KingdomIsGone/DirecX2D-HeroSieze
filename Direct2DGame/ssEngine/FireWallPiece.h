#pragma once
#include "ssGameObject.h"

namespace ss
{
	class FireWallPiece : public GameObject
	{
	public:
		FireWallPiece();
		~FireWallPiece();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Transform* mTransform;
		Vector3 mPos;

		float mDamage;

		class FireWallPieceScript* mScript;
		class Animator* mAnimator;
	};
}