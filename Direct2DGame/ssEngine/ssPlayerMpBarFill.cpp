#include "ssPlayerMpBarFill.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssCamera.h"

namespace ss
{
	PlayerMpBarFill::PlayerMpBarFill()
		: mFullMpScale(1.11f)
		, mCurMpScale(1.11f)
		, mCurMP(1000.0f)
		, mFullMP(1000.0f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.11f, 0.03f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		pos.x += -1.85f;
		pos.y += 1.36f;
		pos.z -= 0.02f;
		mTransform->SetPosition(pos);
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MpBarMater"));

		mWidth = mTransform->GetWorldRightCenter().x - mTransform->GetWorldLeftCenter().x;

		mMpChanged = true;
	}
	PlayerMpBarFill::~PlayerMpBarFill()
	{
	}
	void PlayerMpBarFill::Initialize()
	{
		GameObject::Initialize();
	}
	void PlayerMpBarFill::Update()
	{
		GameObject::Update();

		float ratio = mCurMP / mFullMP;
		mCurMpScale = mFullMpScale * ratio;

		if (mMpChanged)
		{
			Vector3 pos = mTransform->GetPosition();
			float ratio = mCurMpScale / mFullMpScale;
			pos.x = -1.85f;
			pos.x -= (1 - ratio) * mWidth * 0.5f;
			mTransform->SetPosition(pos);

			mTransform->SetScale(Vector3(mCurMpScale, 0.03f, 1.0f));
			mMpChanged = false;
		}
	}
	void PlayerMpBarFill::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void PlayerMpBarFill::Render()
	{
		GameObject::Render();
	}
}
