#include "ssPlayerHpBarFill.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssCamera.h"

namespace ss
{
	PlayerHpBarFill::PlayerHpBarFill()
		: mFullHpScale(1.33f)
		, mCurHpScale(1.33f)
		, mCurHP(3000.0f)
		, mFullHP(3000.0f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.33f, 0.03f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		pos.x += -1.74f;
		pos.y += 1.44f;
		pos.z -= 0.02f;
		mTransform->SetPosition(pos);
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"PlayerHpSmallBarFillRedMater"));

		mWidth = mTransform->GetWorldRightCenter().x - mTransform->GetWorldLeftCenter().x;

		mHpChanged = true;
	}
	PlayerHpBarFill::~PlayerHpBarFill()
	{
	}
	void PlayerHpBarFill::Initialize()
	{
		GameObject::Initialize();
	}
	void PlayerHpBarFill::Update()
	{
		GameObject::Update();

		float ratio = mCurHP / mFullHP;
		mCurHpScale = mFullHpScale * ratio;

		if (mHpChanged)
		{
			Vector3 pos = mTransform->GetPosition();
			float ratio = mCurHpScale / mFullHpScale;
			pos.x = -1.74f;
			pos.x -= (1 - ratio) * mWidth * 0.5f;
			mTransform->SetPosition(pos);

			mTransform->SetScale(Vector3(mCurHpScale, 0.03f, 1.0f));
			mHpChanged = false;
		}
	}
	void PlayerHpBarFill::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void PlayerHpBarFill::Render()
	{
		GameObject::Render();
	}
}
