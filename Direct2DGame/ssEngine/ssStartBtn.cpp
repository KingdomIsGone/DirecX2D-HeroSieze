#include "ssStartBtn.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssFontWrapper.h"

namespace ss
{
	StartBtn::StartBtn()
		: mClicked(false)
	{
		GetComponent<Transform>()->SetScale(1.2f, 0.3f, 1.0f);
		GetComponent<Transform>()->SetPosition(-1.7f, 0.3f, 1.28f);
		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"StartBtn0Mater"));
	}
	StartBtn::~StartBtn()
	{
	}
	void StartBtn::Initialize()
	{
		GameObject::Initialize();
	}
	void StartBtn::Update()
	{
		GameObject::Update();

		if (mClicked)
			SetBtn2();
		else
			SetBtn1();
	}
	void StartBtn::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void StartBtn::Render()
	{
		GameObject::Render();
		FontWrapper::DrawFont(L"PLAY", 215.f, 270.f, 35.f, FONT_RGBA(255, 255, 255, 255));
	}
	void StartBtn::SetBtn1()
	{
		mRenderer->SetNoRender(false);
		mRenderer->SetMaterial(Resources::Find<Material>(L"StartBtn0Mater"));
	}
	void StartBtn::SetBtn2()
	{
		mRenderer->SetNoRender(false);
		mRenderer->SetMaterial(Resources::Find<Material>(L"StartBtn1Mater"));
	}
}
