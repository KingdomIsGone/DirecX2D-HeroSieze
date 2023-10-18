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

		void SetItmeHave(UINT num);

	private:
		Transform* mTransform;
		Vector3 mPos;

		class EntScript* mScript;
		class EnemyHpBar* mHpBar;
		class EnemyHpBarFill* mHpBarFill;

		float mPrevHp;
		float mCurHp;
	};
}