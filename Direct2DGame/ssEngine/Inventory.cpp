#include "Inventory.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssLight.h"
#include "ssEquipmentSlot.h"

namespace ss
{
	Inventory::Inventory()
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(5.5f, 2.8f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		pos.z -= 0.2f;
		mTransform->SetPosition(pos);

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));

		mLight = nullptr;
		mOn = false;

		
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
		}
		else
		{
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));

			for (EquipmentSlot* slot : mEquipSlots)
			{
				slot->SetBlank();
			}
		}
	}

}
