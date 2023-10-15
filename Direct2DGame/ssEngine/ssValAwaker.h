#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ValAwaker : public GameObject
	{
	public:
		ValAwaker();
		~ValAwaker();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetTouched() { mbTouched = true; }
		bool GetTouched() { return mbTouched; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		class Collider2D* mCollider;
		class AwakerScript* mScript;

		bool mbTouched;
	};
}