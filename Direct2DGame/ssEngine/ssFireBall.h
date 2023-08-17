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

		float GetDamage() { return mDamage; }
		void SetForInstance(bool is) { mForInstance = is; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		Vector2 mDirVector;
		float mSpeed;
		float mDeleteTime;
		float mDamage;
		bool mForInstance;

		class Collider2D* mCollider;
	};
}