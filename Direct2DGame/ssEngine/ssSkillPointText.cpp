#include "ssSkillPointText.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"

namespace ss
{
	SkillPointText::SkillPointText(GameObject* parent)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.4f, 0.12f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		mTransform->SetPosition(Vector3(0.0f, 0.0f, 0.74f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		mRenderer->SetMaterial(Resources::Find<Material>(L"skillPointMater"));
	}

	SkillPointText::~SkillPointText()
	{
	}

	void SkillPointText::Initialize()
	{
		SkillPointText::Initialize();
	}
	void SkillPointText::Update()
	{
		GameObject::Update();

	}
	void SkillPointText::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void SkillPointText::Render()
	{
		if(mOn)
			GameObject::Render();
	}

}