#pragma once
class LightBall
{
};

#pragma once
#include "ssGameObject.h"

namespace ss
{
	class LightBall : public GameObject
	{
	public:
		LightBall(e4Direction dir);
		~LightBall();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		static float GetDamage() { return mDamage; }

	private:
		e4Direction mDir;
		Transform* mTransform;
		Vector3 mPos;
		float mSpeed;

		float mDeleteTime;

		class Collider2D* mCollider;

		static float mDamage;
	};
}
