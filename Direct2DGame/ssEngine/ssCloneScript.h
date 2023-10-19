#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class CloneScript : public Script
	{
	public:
		CloneScript();
		~CloneScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void LightningAssault();

		void SetClone(class CloneAssault* clone) { mClone = clone; }
		void SetDir(e4Direction dir) { mDir = dir; }
		void SetBeforePos(Vector3 pos) { mRushBeforePos = pos; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetStart() { mStart = true; }

	private:
		float mSpeed;
		e4Direction mDir;

		Transform* mTransform;
		Vector3 mPos;
		Vector3 mPlayerPos;

		bool mStart;

		//Rush
		UINT mRushStage;
		float mRushReadySpeed;
		float mRushAxisDist;
		Vector3 mRushBeforePos;
		float mRushBackDist;
		float mRushDistRow;
		float mRushDistCol;
		float mRushSpeed;

		//Assault
		UINT mEffectCount;
		float mBackdistance;
		bool mAssaultSndOnce;
		bool mMakeSndOnce;
		
		class Animator* mAnimator;
		class Collider2D* mCollider;
		class ValThunderEffect* mThunderEffect;
		class CloneAssault* mClone;
		class AudioSource* mAs;
	};
}
