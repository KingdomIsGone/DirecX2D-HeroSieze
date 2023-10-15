#pragma once
#include "ssGameObject.h"

namespace ss
{
	class BossHpFill : public GameObject
	{
	public:
		BossHpFill();
		~BossHpFill();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void setPos(Vector3 pos) { mPos = pos; }

		void SetIniHp(float hp) { mCurHP = hp; mPrevHP = hp; mFullHP = hp; }
		void ChangeHP(float hp) {  mCurHP = hp; }
		void SetBlank();
		void SetMater();

	private:
		Transform* mTransform;
		Vector3 mPos;
		float mFullHpScale;
		float mCurHpScale;
		float mWidth;
		bool mHpChanged;
		float mCurHP;
		float mPrevHP;
		float mFullHP;

		class MeshRenderer* mRenderer;
	};
}