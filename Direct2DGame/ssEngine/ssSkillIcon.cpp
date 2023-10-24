#include "ssSkillIcon.h"
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
	SkillIcon::SkillIcon(GameObject* parent)
		: mPoint(0)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(0.24f, 0.24f, 1.f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		

	}

	SkillIcon::~SkillIcon()
	{
	}

	void SkillIcon::Initialize()
	{
		GameObject::Initialize();
	}
	void SkillIcon::Update()
	{
		GameObject::Update();

		/*if(mLearn)
			mRenderer->SetMaterial()*/

	}
	void SkillIcon::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void SkillIcon::Render()
	{
		if (mOn)
		{
			GameObject::Render();


			//FontWrapper::DrawFont(IntToWchar(mPoint), 400, 538, 20, FONT_RGBA(255, 255, 255, 255));
		}

	}

}