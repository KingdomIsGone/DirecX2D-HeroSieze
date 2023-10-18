#pragma once
#include "ssGameObject.h"

namespace ss
{
	class DesertArcher : public GameObject
	{
	public:
		DesertArcher();
		~DesertArcher();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetItmeHave(UINT num);

	private:
		Transform* mTransform;
		Vector3 mPos;

		class DesertArcherScript* mScript;
		class EnemyHpBar* mHpBar;
		class EnemyHpBarFill* mHpBarFill;

		float mPrevHp;
		float mCurHp;
	};
}