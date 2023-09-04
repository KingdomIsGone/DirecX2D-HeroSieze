#include "ssSkillSlot1.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

namespace ss
{
	SkillSlot1::SkillSlot1()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MeteorIconMater"));
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(0.24f, 0.24f, 1.0f);
	}
	SkillSlot1::~SkillSlot1()
	{
	}
	void SkillSlot1::Initialize()
	{
		GameObject::Initialize();
	}
	void SkillSlot1::Update()
	{
		GameObject::Update();
	}
	void SkillSlot1::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void SkillSlot1::Render()
	{
		GameObject::Render();
	}
}
