#pragma once
#include "ssGameObject.h"

namespace ss
{
	class EnemyHpBarFill : public GameObject
	{
	public:
		EnemyHpBarFill();
		~EnemyHpBarFill();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void setPos(Vector3 pos) { mPos = pos; }

		void ChangeHP(float hp) { mHpChanged = true; mCurHP = hp; }

		void SetOwnerTransform(Transform* tr) { mOwnerTransform = tr; }
		void SetOffset(float x, float y) { mOffsetX = x; mOffsetY = y; }
		void SetFullHp(float full) { mFullHP = full; mCurHP = full; }

		void SetFullScale(float x, float y);

	private:
		Transform* mTransform;
		Transform* mOwnerTransform;

		float mOffsetX;
		float mOffsetY;

		float mModifyX;

		Vector3 mPos;
		float mFullHpScale;
		float mCurHpScale;
		float mScaleY;
		float mWidth;
		bool mHpChanged;
		float mCurHP;
		float mFullHP;
	};
}
