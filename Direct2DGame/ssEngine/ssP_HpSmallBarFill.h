#pragma once
#include "ssGameObject.h"

namespace ss
{
	class P_HpSmallBarFill : public GameObject
	{
	public:
		P_HpSmallBarFill();
		~P_HpSmallBarFill();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void setPos(Vector3 pos) { mPos = pos; }

		void ChangeHP(float hp) { mHpChanged = true; mCurHP = hp; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		float mFullHpScale;
		float mCurHpScale;
		float mWidth;
		bool mHpChanged;
		float mCurHP;
		float mFullHP;

		float mModifyX;
	};
}
