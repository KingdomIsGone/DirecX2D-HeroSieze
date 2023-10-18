#pragma once
#include "ssGameObject.h"

namespace ss
{
	class DesertDoor : public GameObject
	{
	public:
		DesertDoor();
		~DesertDoor();

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