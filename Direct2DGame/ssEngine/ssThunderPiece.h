#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ThunderPiece : public GameObject
	{
	public:
		ThunderPiece(GameObject* parent);
		~ThunderPiece();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindCB(float Radd, float Gadd, float Badd, float A);

		void SetOffset(Vector3 offset) { mOffset = offset; }
		Vector3 GetOffset() { return mOffset; }
		void SetPosition(Vector3 pos);
		void SetRotation(Vector3 degree);

	private:
		Transform* mTransform;
		Vector3 mPos;
		Vector3 mOffset;
		Vector3 mValkPos;


		class Animator* mAnimator;

	};
}