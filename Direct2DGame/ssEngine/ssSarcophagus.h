#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Sarcophagus : public GameObject
	{
	public:
		enum class eDir
		{
			LeftTop,
			RightTop,
			LeftBottom,
			RightBottom,
		};
		Sarcophagus();
		~Sarcophagus();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void ChangeHp(float value) { mCurHp += value; }
		void DamageCheck();
		void SummonMummy();

		void SetDir(eDir dir) { mDir = dir; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		eDir mDir;

		class EnemyHpBar* mHpBar;
		class EnemyHpBarFill* mHpBarFill;

		float mPrevHp;
		float mCurHp;

		float mSpawnTime;
	};
}