#include "ssBossHpBar.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"

namespace ss
{
	BossHpBar::BossHpBar()
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(2.2f, 0.2f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		mTransform->SetPosition(pos);

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}

	BossHpBar::~BossHpBar()
	{
	}

	void BossHpBar::Initialize()
	{
		GameObject::Initialize();
	}
	void BossHpBar::Update()
	{
		GameObject::Update();
	}
	void BossHpBar::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void BossHpBar::Render()
	{
		GameObject::Render();
	}

	void BossHpBar::SetHP()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"BossHpBarMater"));
	}

	void BossHpBar::SetBlank()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	
}
