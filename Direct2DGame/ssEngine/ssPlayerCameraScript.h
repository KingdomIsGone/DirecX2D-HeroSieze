#pragma once
//#include "ssScript.h"
#include <ssScript.h>

namespace ss
{
	class PlayerCameraScript : public Script
	{
	public:
		virtual void Update() override;


		//virtual void OnCollisionEnter(Collider2D* other) override;
		//virtual void OnCollisionStay(Collider2D* other) override;
		//virtual void OnCollisionExit(Collider2D* other) override;

	private:
		Vector3 mPrevPos;
		Vector3 mCurPos;
		Vector3 mDistance;

	};
}

