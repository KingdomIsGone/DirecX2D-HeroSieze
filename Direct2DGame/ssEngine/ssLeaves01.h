#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Leaves01 : public GameObject
	{
	public:
		Leaves01();
		~Leaves01();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindCB(float alpha);
		void SetAlpha(float alpha) { mAlpha = alpha; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		class Collider2D* mCollider;
		class LeavesScript* mScript;

		bool mbTouched;

		float mAlpha;
	};
}