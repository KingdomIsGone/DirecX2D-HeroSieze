#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Dart : public GameObject
	{
	public:
		Dart(float Degree);
		~Dart();

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