#include "ssSkillSelectImage.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssSkillSelectBox.h"

namespace ss
{
	SkillSelectImage::SkillSelectImage(GameObject* parent)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();
		
		mTransform->SetScale(Vector3(0.24f, 0.24f, 1.f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater")); 

	}

	SkillSelectImage::~SkillSelectImage()
	{
	}

	void SkillSelectImage::Initialize()
	{
		GameObject::Initialize();
	}
	void SkillSelectImage::Update()
	{
		GameObject::Update();


	}
	void SkillSelectImage::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void SkillSelectImage::Render()
	{
		if (mOn && mIn)
			GameObject::Render();
		
	}

	void SkillSelectImage::SetMater()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(mMaterName));
	}

	
}