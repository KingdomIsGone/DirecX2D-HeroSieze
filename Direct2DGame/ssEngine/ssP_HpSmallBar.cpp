#include "ssP_HpSmallBar.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

namespace ss
{
	P_HpSmallBar::P_HpSmallBar()
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.20f, 0.04f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		pos.y += 0.17f;
		pos.z -= 0.01f;
		mTransform->SetPosition(pos);
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"PlayerHpSmallBarMater"));
	}

	P_HpSmallBar::~P_HpSmallBar()
	{
	}

	void P_HpSmallBar::Initialize()
	{
		GameObject::Initialize();
	}
	void P_HpSmallBar::Update()
	{
		GameObject::Update();
	}
	void P_HpSmallBar::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void P_HpSmallBar::Render()
	{
		GameObject::Render();
	}
}
