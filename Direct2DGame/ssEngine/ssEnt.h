#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Ent : public GameObject
	{
	public:
		Ent();
		~Ent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Transform* mTransform;
		Vector3 mPos;

		class EntScript* mMScript;
		class EnemyHpBar* mHpBar;
		class EnemyHpBarFill* mHpBarFill;

		float mPrevHp;
		float mCurHp;
	};
}