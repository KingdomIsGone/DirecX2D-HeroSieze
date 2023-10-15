#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Valkyrie : public GameObject
	{
	public:
		Valkyrie();
		~Valkyrie();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetAhlphaMater(float alpha);

		void SetBossHpFill(class BossHpFill* fill);
		bool GetAwake() { return mbAwake; }
		void SetAwake() { mbAwake = true; }
		bool GetDead() { return mbDead; }
		void SetDead() { mbDead = true; }
		bool GetEventComplete() { return mbEventComplete; }
		void SetEventComplete(bool is) { mbEventComplete = is; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		class ValkyrieScript* mScript;
		class Animator* mAnimator;
		class MeshRenderer* mMr;

		UINT mTransformAniStage;

		float mPrevHp;
		float mCurHp;

		class ValEffector* mEffector;
		
		bool mbAwake;
		bool mbEventComplete;
		bool mbDead;
	};
}