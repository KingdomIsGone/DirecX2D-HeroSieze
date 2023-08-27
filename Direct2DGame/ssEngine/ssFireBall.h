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

		void SetForInstance(bool is) { mForInstance = is; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		Vector2 mDirVector;
		float mSpeed;
		float mDeleteTime;
		bool mForInstance;

		class Collider2D* mCollider;
	};
}