#pragma once
//#include "ssScript.h"
#include "..\Engine_SOURCE\ssScript.h"
#include "..\Engine_SOURCE\ssAnimator.h"

namespace ss
{
	class FireWallPieceScript : public Script
	{
	public:
		FireWallPieceScript();
		~FireWallPieceScript();

		virtual void Initialize() override;
		virtual void Update() override;


		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		float mDamage;
		float mTime;

		std::vector<UINT> mColIDs;

	};
}