#include "ssItemList.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssItemBackground.h"
#include "ssItem.h"
#include "ssItemImage.h"
#include "ssITemlistSelectEffect.h"

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
		ItemBackPos.z -= 0.02f;
		mItemImage->GetComponent<Transform>()->SetPosition(ItemBackPos);

		if (mItemIn)
		{
			mItemBack->SetItemIn(true);
			UINT grade = (UINT)mItem->GetItemGrade();
			mItemBack->SetItemGrade(grade);
			mMaterName = mItem->GetMaterName();
			mItemImage->SetItemIn(true);
			mItemImage->SetMaterName(mItem->GetMaterName());
			mSelectEffect->SetItemIn(true);
		}
		else
		{
			mItemBack->SetItemIn(false);
			mItemImage->SetItemIn(false);
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
	}

	void ItemList::SetMaterialName(std::wstring name)
	{
		mMaterName = name;
	}

	void ItemList::SetMater()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"ItemListMater"));
	}

	void ItemList::SetBlank()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
}
