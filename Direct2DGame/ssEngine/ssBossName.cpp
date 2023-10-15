#include "ssBossName.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssFontWrapper.h"

namespace ss
{
	BossName::BossName()
	{
		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));

		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(Vector3(0.0f, 0.0f, 0.9f));
	}
	BossName::~BossName()
	{
	}
	void BossName::Initialize()
	{
		GameObject::Initialize();
	}
	void BossName::Update()
	{
		GameObject::Update();
	}
	void BossName::LateUpdate()
	{
		GameObject::LateUpdate();
		
	}
	void BossName::Render()
	{
		GameObject::Render();

		if (mbOn)
		{
			FontWrapper::DrawFont(mBossName, mX, mY, 30, FONT_RGBA(255.f, 255.f, 255.f, 255.f));
		}
	}
}
