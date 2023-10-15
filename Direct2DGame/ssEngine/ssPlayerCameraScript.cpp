#include "ssPlayerCameraScript.h"
#include "ssTransform.h"
#include "ssGameObject.h"
#include "ssPlayerScript.h"

namespace ss
{
	void PlayerCameraScript::Update()
	{
		if (!mOn)
			return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		/*mPrevPos = mCurPos;
		mCurPos = PlayerScript::GetPlayerPos();

		mDistance = mPrevPos - mCurPos;
		

		pos.x -= mDistance.x;
		pos.y -= mDistance.y;

		tr->SetPosition(pos);*/
		Vector3 cameraPos = PlayerScript::GetPlayerPos();
		cameraPos.z = -10.0f;
		tr->SetPosition(cameraPos);
	}
}
