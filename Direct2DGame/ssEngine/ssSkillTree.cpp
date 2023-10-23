#include "ssSkillTree.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssSkillSelectBox.h"
#include "ssInput.h"
#include "ssDim.h"

namespace ss
{
	SkillTree::SkillTree(GameObject* parent)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(3.f, 3.f, 1.f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"SkillTreeMater")); 
		
	}

	SkillTree::~SkillTree()
	{
	}

	void SkillTree::Initialize()
	{
		GameObject::Initialize();
	}
	void SkillTree::Update()
	{
		GameObject::Update();

		SetOnOffCheck();

	}
	void SkillTree::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void SkillTree::Render()
	{
		if (mOn)
			GameObject::Render();

	}

	void SkillTree::SetOnOffCheck()
	{
		if (Input::GetKeyDown(eKeyCode::T))
		{
			if (mOn)
			{
				mOn = false;
				mDim->SetOnOff(false);
			}
			else
			{
				mOn = true;
				mDim->SetOnOff(true);
			}
		}
	}



}