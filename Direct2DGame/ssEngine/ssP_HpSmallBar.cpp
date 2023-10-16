#include "ssP_HpSmallBar.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssPlayerScript.h"

namespace ss
{
	P_HpSmallBar::P_HpSmallBar()
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.3f, 0.06f, 1.0f));
		
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

		Vector3 pos = PlayerScript::GetPlayerPos();
		pos.x += 0.02f;
		pos.y += 0.19f;
		pos.z = 0.92;
		mTransform->SetPosition(pos);

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
