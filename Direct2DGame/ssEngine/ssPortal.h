#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Portal : public GameObject
	{
	public:
		Portal();
		~Portal();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	private:
		Transform* mTransform;
		Vector3 mPos;

		class Collider2D* mCollider;
	};
}