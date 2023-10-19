#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void DamageCheck();
		void HpCheck();
		void MpCheck();

		class PlayerScript* GetScript() { return mScript; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		float mCurHp;
		float mPrevHp;
		float mCurMp;
		float mPrevMp;

		class PlayerScript* mScript;
		class P_HpSmallBar* mSmallHpBar;
		class P_HpSmallBarFill* mSmallHpBarFill;
		class PlayerHpBarFill* mHpBarFill;
		class PlayerMpBarFill* mMpBarFill;

		
	};
}