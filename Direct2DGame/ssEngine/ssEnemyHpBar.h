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

	private:
		Transform* mTransform;
		Vector3 mPos;

	};
}
