#include "ssNumber.h"
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
	Number::Number(GameObject* parent)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(0.07f, 0.07f, 1.f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"SkillLevMater"));

	}

	Number::~Number()
	{
	}

	void Number::Initialize()
	{
		GameObject::Initialize();
	}
	void Number::Update()
	{
		GameObject::Update();

		if(mNum == 0)
			mRenderer->SetMaterial(Resources::Find<Material>(L"Number0Mater"));
		else if(mNum == 1)
			mRenderer->SetMaterial(Resources::Find<Material>(L"Number1Mater"));
		else if (mNum == 2)
			mRenderer->SetMaterial(Resources::Find<Material>(L"Number2Mater"));
		else if (mNum == 3)
			mRenderer->SetMaterial(Resources::Find<Material>(L"Number3Mater"));
		else if (mNum == 4)
			mRenderer->SetMaterial(Resources::Find<Material>(L"Number4Mater"));
		else if (mNum == 5)
			mRenderer->SetMaterial(Resources::Find<Material>(L"Number5Mater"));
		else if (mNum == 6)
			mRenderer->SetMaterial(Resources::Find<Material>(L"Number6Mater"));
		else if (mNum == 7)
			mRenderer->SetMaterial(Resources::Find<Material>(L"Number7Mater"));
		else if (mNum == 8)
			mRenderer->SetMaterial(Resources::Find<Material>(L"Number8Mater"));
		else if (mNum == 9)
			mRenderer->SetMaterial(Resources::Find<Material>(L"Number9Mater"));


	}
	void Number::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Number::Render()
	{
		if (mOn)
		{
			GameObject::Render();
		}

	}


}