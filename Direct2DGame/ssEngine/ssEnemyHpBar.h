#pragma once
#include "ssGameObject.h"

namespace ss
{
	class EnemyHpBar : public GameObject
	{
	public:
		EnemyHpBar();
		~EnemyHpBar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void setPos(Vector3 pos) { mPos = pos; }
		void SetOwnerTransform(Transform* tr) { mOwnerTransform = tr; }
		void SetOffset(float x, float y) { mOffsetX = x; mOffsetY = y; }

	private:
		Transform* mTransform;
		Transform* mOwnerTransform;
		Vector3 mPos;

		float mOffsetX;
		float mOffsetY;

		static UINT mCount;
		UINT mThisCount;
	};
}
