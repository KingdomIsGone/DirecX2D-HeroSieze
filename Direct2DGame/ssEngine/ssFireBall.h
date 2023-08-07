#pragma once
#include "ssGameObject.h"

namespace ss
{
	class FireBall : public GameObject
	{
	public:
		FireBall(float Degree);
		~FireBall();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;



	private:
		Transform* mTransform;
		Vector3 mPos;
		float mSpeed;
		Vector2 mDirVector;
		float mDeleteTime;

		class Collider2D* mCollider;
	};
}