#include "Inventory.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssLight.h"
#include "ssEquipmentSlot.h"
#include "ssItemList.h"

namespace ss
{
	Inventory::Inventory(GameObject* obj)
	{
		SetName(L"Inventory");
		SetParent(obj);
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(5.5f, 2.8f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		pos.z -= 0.1f;
		mTransform->SetPosition(pos);

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));

		mLight = nullptr;
		mOn = false;

		mList1 = new ItemList(this);
		mList1->GetComponent<Transform>()->SetScale(1.42f, 0.6f, 1.0f);
		Vector3 List1Pos = mList1->GetComponent<Transform>()->GetPosition();
		List1Pos.x += 0.39f;
		List1Pos.y += 1.f;
		mList1->GetComponent<Transform>()->SetPosition(List1Pos);
		AddOtherGameObject(mList1, eLayerType::Inventory);

		ItemList* mList2 = new ItemList(this);
		mList2->GetComponent<Transform>()->SetScale(1.42f, 0.6f, 1.0f);
		Vector3 List2Pos = mList2->GetComponent<Transform>()->GetPosition();
		List2Pos.x += 0.39f;
		List2Pos.y += 0.4f;
		mList2->GetComponent<Transform>()->SetPosition(List2Pos);
		AddOtherGameObject(mList2, eLayerType::Inventory);

		ItemList* mList3 = new ItemList(this);
		mList3->GetComponent<Transform>()->SetScale(1.42f, 0.6f, 1.0f);
		Vector3 List3Pos = mList3->GetComponent<Transform>()->GetPosition();
		List3Pos.x += 0.39f;
		List3Pos.y += -0.2f;
		mList3->GetComponent<Transform>()->SetPosition(List3Pos);
		AddOtherGameObject(mList3, eLayerType::Inventory);

		mItemLists.push_back(mList1);
		mItemLists.push_back(mList2);
		mItemLists.push_back(mList3);
	}

	Inventory::~Inventory()
	{
	}

	void Inventory::Initialize()
	{
		GameObject::Initialize();
	}
	void Inventory::Update()
	{
		GameObject::Update();

		OnOffCheck();
		
		Vector3 pos = mTransform->GetPosition();
	}
	void Inventory::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Inventory::Render()
	{
		GameObject::Render();
	}

	void Inventory::OnOffCheck()
	{
		if (Input::GetKeyDown(eKeyCode::C))
		{
			if (mOn)
			{
				mOn = false;
				mLight->SetColor(Vector4(0.f, 0.f, 0.f, 0.f));
			}
			else
			{
				mOn = true;
				mLight->SetColor(Vector4(-1.0f, -1.0f, -1.0f, 1.f));
			}
		}

		if (mOn)
		{
			mRenderer->SetMaterial(Resources::Find<Material>(L"InventoryMater"));

			for (EquipmentSlot* slot : mEquipSlots)
			{
				slot->SetMater();
			}

			for (ItemList* list : mItemLists)
			{
				if (list->GetItemIn())
					list->SetMater();
				else
					list->SetBlank();
			}
		}
		else
		{
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));

			for (EquipmentSlot* slot : mEquipSlots)
			{
				slot->SetBlank(); 
			}

			for (ItemList* list : mItemLists)
			{
				list->SetBlank();
			}
		}
	}

}
