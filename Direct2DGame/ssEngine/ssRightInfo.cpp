#include "ssRightInfo.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssItem.h"
#include "ssItemBackground.h"
#include "ssFontWrapper.h"

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
		if (mOn)
		{
			int fontColor[3] = {};
			eItemGrade grade = mItem->GetItemGrade();
			if (grade == eItemGrade::Normal)
			{
				fontColor[0] = 255;
				fontColor[1] = 255;
				fontColor[2] = 255;
			}
			else if (grade == eItemGrade::Magic)
			{
				fontColor[0] = 0;
				fontColor[1] = 0;
				fontColor[2] = 255;
			}
			else if (grade == eItemGrade::Legend)
			{
				fontColor[0] = 218;
				fontColor[1] = 165;
				fontColor[2] = 32;
			}

			FontWrapper::DrawFont(mItem->GetItemName(), 960.f, 100.f, 20
				, FONT_RGBA(fontColor[0], fontColor[1], fontColor[2], 255));
			FontWrapper::DrawFont(mItem->GetItemText(), 960.f, 170.f, 15
				, FONT_RGBA(255, 255, 255, 255));
		}
	}

	void RightInfo::SetBlank()
	{
		//mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
		mRenderer->SetNoRender(true);
	}
}