#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Mummy : public GameObject
	{
	public:
		Mummy();
		~Mummy();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Transform* mTransform;
		Vector3 mPos;

		class MummyScript* mScript;
		class EnemyHpBar* mHpBar;
		class EnemyHpBarFill* mHpBarFill;

		float mPrevHp;
		float mCurHp;
	};
}