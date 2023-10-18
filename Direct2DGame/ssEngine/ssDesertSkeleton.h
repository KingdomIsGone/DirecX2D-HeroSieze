#pragma once
#include "ssGameObject.h"

namespace ss
{
	class DesertSkeleton : public GameObject
	{
	public:
		DesertSkeleton();
		~DesertSkeleton();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetItmeHave(UINT num);

	private:
		Transform* mTransform;
		Vector3 mPos;

		class SkeletonScript* mScript;
		class EnemyHpBar* mHpBar;
		class EnemyHpBarFill* mHpBarFill;

		float mPrevHp;
		float mCurHp;
	};
}