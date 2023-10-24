#include "ssSkillLevel.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssSkillSelectBox.h"
#include "ssInput.h"
#include "ssDim.h"
#include "ssFontWrapper.h"
#include "ssSkillPointText.h"
#include "ssFontWrapper.h"

namespace ss
{
	SkillLevel::SkillLevel(GameObject* parent)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(0.1f, 0.1f, 1.f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"SkillLevMater"));

		
	}

	SkillLevel::~SkillLevel()
	{
	}

	void SkillLevel::Initialize()
	{
		GameObject::Initialize();
	}
	void SkillLevel::Update()
	{
		GameObject::Update();


	}
	void SkillLevel::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void SkillLevel::Render()
	{
		if (mOn)
		{
			GameObject::Render();
		}

	}


}