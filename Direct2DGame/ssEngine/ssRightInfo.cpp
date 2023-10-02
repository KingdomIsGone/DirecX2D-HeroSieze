#include "ssRightInfo.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssItem.h"
#include "ssItemBackground.h"

namespace ss
{
	RightInfo::RightInfo(GameObject* parent)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();
		Vector3 pos = mTransform->GetPosition();
		mTransform->SetPosition(pos);
		mTransform->SetScale(Vector3(0.4f, 0.5f, 1.f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));

	}

	RightInfo::~RightInfo()
	{
	}

	void RightInfo::Initialize()
	{
		GameObject::Initialize();
	}
	void RightInfo::Update()
	{
		GameObject::Update();

		if (mOn)
		{
			mRenderer->SetNoRender(false);
			mRenderer->SetMaterial(Resources::Find<Material>(mItem->GetMaterName()));
			mItemBack->SetItemGrade((UINT)mItem->GetItemGrade());
			mItemBack->SetOnList(true);
		}
		else
		{
			SetBlank();
			mItemBack->SetBlank();
			mItemBack->SetOnList(false);
		}

	}
	void RightInfo::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void RightInfo::Render()
	{
		GameObject::Render();
	}

	void RightInfo::SetBlank()
	{
		//mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
		mRenderer->SetNoRender(true);
	}
}