#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Arrow : public GameObject
	{
	public:
		Arrow(float Degree);
		~Arrow();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	private:
		Transform* mTransform;
		Vector3 mPos;
		Vector2 mDirVector;
		float mSpeed;
		float mDeleteTime;

		class Collider2D* mCollider;
	};
}