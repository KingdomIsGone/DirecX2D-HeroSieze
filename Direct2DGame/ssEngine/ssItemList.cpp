#include "ssItemList.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssItemBackground.h"
#include "ssItem.h"
#include "ssItemImage.h"
#include "ssITemlistSelectEffect.h"
#include "ssFontWrapper.h"

namespace ss
{
	ItemList::ItemList(GameObject* parent)
		: mItem(nullptr)
		, mItemImage(nullptr)
		, mSelected(false)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();
		mPos = mTransform->GetPosition();
		mPos.z -= 0.11f;
		mTransform->SetPosition(mPos);

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"ItemListMater"));

		mItemBack = new ItemBackground(this);
		AddOtherGameObject(mItemBack, eLayerType::Inventory);

		mItemImage = new ItemImage(this);
		AddOtherGameObject(mItemImage, eLayerType::Inventory);

		
	}

	ItemList::~ItemList()
	{
	}

	void ItemList::Initialize()
	{
		GameObject::Initialize();
	}
	void ItemList::Update()
	{
		GameObject::Update();
		mPos = mTransform->GetPosition();
		Vector3 ItemBackPos = mPos;
		ItemBackPos.z -= 0.01f;
		ItemBackPos.x -= 0.42f;
		mItemBack->GetComponent<Transform>()->SetPosition(ItemBackPos);
		ItemBackPos.z -= 0.03f;
		mItemImage->GetComponent<Transform>()->SetPosition(ItemBackPos);

		if (mItemIn)
		{
			mItemBack->SetOnList(true);
			UINT grade = (UINT)mItem->GetItemGrade();
			mItemBack->SetItemGrade(grade);
			mMaterName = mItem->GetMaterName();
			mItemImage->SetOnList(true);
			mItemImage->SetMaterName(mItem->GetMaterName());
			mSelectEffect->SetItemIn(true);
		}
		else
		{
			mItemBack->SetOnList(false);
			mItemImage->SetOnList(false);
			mSelectEffect->SetItemIn(false);
		}

		if (mSelected)
		{
			mSelectEffect->SetSelected(true);

		}
		else
		{
			mSelectEffect->SetSelected(false);
		}
	}

	void ItemList::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void ItemList::Render()
	{
		GameObject::Render();
		if (mItem != nullptr && mItemIn)
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

			if (mListNum == 1)
			{
				FontWrapper::DrawFont(mItem->GetItemName(), 650.f, 100.f, 20
					, FONT_RGBA(fontColor[0], fontColor[1], fontColor[2], 255));
				FontWrapper::DrawFont(mItem->GetItemText(), 650.f, 170.f, 15
					, FONT_RGBA(255, 255, 255, 255));
			}
			else if (mListNum == 2)
			{
				FontWrapper::DrawFont(mItem->GetItemName(), 650.f, 220.f, 20
					, FONT_RGBA(fontColor[0], fontColor[1], fontColor[2], 255));
				FontWrapper::DrawFont(mItem->GetItemText(), 650.f, 290.f, 15
					, FONT_RGBA(255, 255, 255, 255));
			}
			else if (mListNum == 3)
			{
				FontWrapper::DrawFont(mItem->GetItemName(), 650.f, 340.f, 20
					, FONT_RGBA(fontColor[0], fontColor[1], fontColor[2], 255));
				FontWrapper::DrawFont(mItem->GetItemText(), 650.f, 410.f, 15
					, FONT_RGBA(255, 255, 255, 255));

			}
		}
	}

	void ItemList::SetMaterialName(std::wstring name)
	{
		mMaterName = name;
	}

	void ItemList::SetMater()
	{
		mRenderer->SetNoRender(false);
		mRenderer->SetMaterial(Resources::Find<Material>(L"ItemListMater"));
	}

	void ItemList::SetBlank()
	{
		//mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
		mRenderer->SetNoRender(true);
	}
}
