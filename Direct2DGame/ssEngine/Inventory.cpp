#include "Inventory.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssLight.h"
#include "ssEquipmentSlot.h"
#include "ssItemList.h"
#include "ssItem.h"
#include "ssCursor.h"
#include "ssPlayerScript.h"
#include "ssItemBackground.h"
#include "ssItemImage.h"
#include "ssITemlistSelectEffect.h"

namespace ss
{
	std::vector<class Item*> ss::Inventory::mWeapons = {};
	std::vector<Item*> ss::Inventory::mArmors = {};
	std::vector<Item*> ss::Inventory::mShields = {};
	std::vector<Item*> ss::Inventory::mHelmets = {};
	std::vector<Item*> ss::Inventory::mBelts = {};
	std::vector<Item*> ss::Inventory::mShoes = {};

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

		//list1
		mList1 = new ItemList(this);
		mList1->GetComponent<Transform>()->SetScale(1.42f, 0.6f, 1.0f);
		Vector3 List1Pos = mList1->GetComponent<Transform>()->GetPosition();
		List1Pos.x += 0.39f;
		List1Pos.y += 1.f;
		mList1->GetComponent<Transform>()->SetPosition(List1Pos);
		AddOtherGameObject(mList1, eLayerType::Inventory);

		ITemlistSelectEffect* SelectEffect1  = new ITemlistSelectEffect(this);
		SelectEffect1->GetComponent<Transform>()->
			SetPosition(Vector3(List1Pos.x, List1Pos.y + 0.01f, List1Pos.z - 0.1f));
		AddOtherGameObject(SelectEffect1, eLayerType::Inventory);
		mList1->SetEffect(SelectEffect1);

		//list2
		mList2 = new ItemList(this);
		mList2->GetComponent<Transform>()->SetScale(1.42f, 0.6f, 1.0f);
		Vector3 List2Pos = mList2->GetComponent<Transform>()->GetPosition();
		List2Pos.x += 0.39f;
		List2Pos.y += 0.4f;
		mList2->GetComponent<Transform>()->SetPosition(List2Pos);
		AddOtherGameObject(mList2, eLayerType::Inventory);

		ITemlistSelectEffect* SelectEffect2 = new ITemlistSelectEffect(this);
		SelectEffect2->GetComponent<Transform>()->
			SetPosition(Vector3(List2Pos.x, List2Pos.y + 0.01f, List2Pos.z - 0.1f));
		AddOtherGameObject(SelectEffect2, eLayerType::Inventory);
		mList2->SetEffect(SelectEffect2);

		//list3
		mList3 = new ItemList(this);
		mList3->GetComponent<Transform>()->SetScale(1.42f, 0.6f, 1.0f);
		Vector3 List3Pos = mList3->GetComponent<Transform>()->GetPosition();
		List3Pos.x += 0.39f;
		List3Pos.y += -0.2f;
		mList3->GetComponent<Transform>()->SetPosition(List3Pos);
		AddOtherGameObject(mList3, eLayerType::Inventory);

		ITemlistSelectEffect* SelectEffect3 = new ITemlistSelectEffect(this);
		SelectEffect3->GetComponent<Transform>()->
			SetPosition(Vector3(List3Pos.x, List3Pos.y + 0.01f, List3Pos.z - 0.1f));
		AddOtherGameObject(SelectEffect3, eLayerType::Inventory);
		mList3->SetEffect(SelectEffect3);

		mItemLists.push_back(mList1);
		mItemLists.push_back(mList2);
		mItemLists.push_back(mList3);

		mItemKindMask.reset();
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
		CursorOnEquipCheck();
		CursorOnListCheck();
		
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
				slot->GetItemBack()->SetBlank();
			}

			for (ItemList* list : mItemLists)
			{
				list->SetBlank();
				list->SetItemIn(false);
			}
		}
	}

	void Inventory::CursorOnEquipCheck()
	{
		if (!mOn)
			return;

		Vector3 cursorPos = Cursor::GetPos();
		Vector3 playerPos = PlayerScript::GetPlayerPos();
		cursorPos -= playerPos;

		for (size_t i = 0; i < (UINT)eKind::End; i++)
		{
			Transform* tr = mEquipSlots[i]->GetComponent<Transform>();
			Vector2 LBpos = tr->GetWorldLeftBottom();
			Vector2 RTpos = tr->GetWorldRightUp();

			if (LBpos.x <= cursorPos.x && cursorPos.x <= RTpos.x
				&& LBpos.y <= cursorPos.y && cursorPos.y <= RTpos.y)
			{
				if (Input::GetKeyDown(eKeyCode::LBUTTON))
				{
					mItemKindMask.reset();
					mItemKindMask.set(i, true);
					ActivateItemList(i);
				}
			}
		}
		
	}

	void Inventory::CursorOnListCheck()
	{
		if (!mOn)
			return;

		Vector3 cursorPos = Cursor::GetPos();
		Vector3 playerPos = PlayerScript::GetPlayerPos();
		cursorPos -= playerPos;

		for (int i = 0; i < mItemLists.size(); i++)
		{
			if (!mItemLists[i]->GetItemIn())
				break;

			Transform* tr = mItemLists[i]->GetComponent<Transform>();
			Vector2 LBpos = tr->GetWorldLeftBottom();
			Vector2 RTpos = tr->GetWorldRightUp();

			if (LBpos.x <= cursorPos.x && cursorPos.x <= RTpos.x
				&& LBpos.y <= cursorPos.y && cursorPos.y <= RTpos.y)
			{
				if (Input::GetKeyDown(eKeyCode::LBUTTON))
				{
					for (int i = 0; i < mItemLists.size(); i++)
					{
						mItemLists[i]->SetSelected(false);
					}
					mItemLists[i]->SetSelected(true);
				}
			}
		}

		
	}

	void Inventory::ActivateItemList(UINT num)
	{
		std::vector<Item*> items;

		eKind kind = (eKind)num;

		switch (kind)
		{
		case ss::Inventory::eKind::Weapon:
			items = mWeapons;
			break;
		case ss::Inventory::eKind::Armor:
			items = mArmors;
			break;
		case ss::Inventory::eKind::Shield:
			items = mShields;
			break;
		case ss::Inventory::eKind::Helmet:
			items = mHelmets;
			break;
		case ss::Inventory::eKind::Belt:
			items = mBelts;
			break;
		case ss::Inventory::eKind::Shoes:
			items = mShoes;
			break;
		case ss::Inventory::eKind::End:
			break;
		default:
			break;
		}

		for (size_t i = 0; i < mItemLists.size(); i++)
		{
			mItemLists[i]->SetItemIn(false);
			mItemLists[i]->SetItem(nullptr);
		}

		for (int i = 0; i < items.size(); i++)
		{
			mItemLists[i]->SetItemIn(true);
			mItemLists[i]->SetItem(items[i]);
		}
	}

	void Inventory::PushbackItem(Item* item)
	{
		UINT kind = (UINT)item->GetItemKind();
		if (kind == 0)
			mWeapons.push_back(item);
		else if(kind == 1)
			mArmors.push_back(item);
		else if (kind == 2)
			mShields.push_back(item);
		else if (kind == 3)
			mHelmets.push_back(item);
		else if (kind == 4)
			mBelts.push_back(item);
		else if (kind == 5)
			mShoes.push_back(item);
	}


}
