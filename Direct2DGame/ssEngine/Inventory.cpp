#include "Inventory.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

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

		mOn = true;
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

		if(mOn)
			mRenderer->SetMaterial(Resources::Find<Material>(L"InventoryMater"));
		else
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	void Inventory::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Inventory::Render()
	{
		GameObject::Render();
	}


}
