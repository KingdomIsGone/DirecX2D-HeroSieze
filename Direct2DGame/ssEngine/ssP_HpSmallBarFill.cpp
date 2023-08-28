#include "ssP_HpSmallBarFill.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssCamera.h"

namespace ss
{
	P_HpSmallBarFill::P_HpSmallBarFill()
		: mFullHpScale(0.14f)
		, mCurHpScale(0.14f)
		, mCurHP(3000.0f)
		, mFullHP(3000.0f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(mCurHpScale, 0.018f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		pos.y += 0.174f;
		pos.z -= 0.02f;
		mTransform->SetPosition(pos);
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"PlayerHpSmallBarFillRedMater"));

		mWidth = Resources::Find<Texture>(L"PlayerHpSmallBarFillRedTex")->GetWidth() / 6.f - 0.03;

		mHpChanged = true;
	}
	P_HpSmallBarFill::~P_HpSmallBarFill()
	{
	}
	void P_HpSmallBarFill::Initialize()
	{
		GameObject::Initialize();
	}
	void P_HpSmallBarFill::Update()
	{
		GameObject::Update();

		float ratio = mCurHP / mFullHP;
		mCurHpScale = mFullHpScale * ratio;

		if (mHpChanged)
		{
			Vector3 pos = mTransform->GetPosition();
			float ratio = mCurHpScale / mFullHpScale;
			pos.x = 0.0f;
			pos.x -= (1 - ratio) * mWidth * 0.5f;
			mTransform->SetPosition(pos);

			mTransform->SetScale(Vector3(mCurHpScale, 0.018f, 1.0f));
			mHpChanged = false;
		}
	}
	void P_HpSmallBarFill::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void P_HpSmallBarFill::Render()
	{
		GameObject::Render();
	}
}
