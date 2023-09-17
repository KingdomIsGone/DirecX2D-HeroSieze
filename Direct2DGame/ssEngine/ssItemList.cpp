#include "ssItemList.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssItemBackground.h"

namespace ss
{
	ItemList::ItemList(GameObject* obj)
	{
		SetParent(obj);
		mTransform = GetComponent<Transform>();
		mPos = mTransform->GetPosition();
		mPos.z -= 0.11f;
		mTransform->SetPosition(mPos);

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"ItemListMater"));

		mItemBack = new ItemBackground(this);
		AddOtherGameObject(mItemBack, eLayerType::Inventory);

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

		if (mItemIn)
			mItemBack->SetItemIn(true);
		else
			mItemBack->SetItemIn(false);
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
