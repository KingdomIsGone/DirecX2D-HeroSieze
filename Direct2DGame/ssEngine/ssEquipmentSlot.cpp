#include "ssEquipmentSlot.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssLight.h"

namespace ss
{
	EquipmentSlot::EquipmentSlot()
	{
		mTransform = GetComponent<Transform>();
		Vector3 pos = mTransform->GetPosition();
		pos.z -= 0.22f;
		mTransform->SetPosition(pos);

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));

	}

	EquipmentSlot::~EquipmentSlot()
	{
	}

	void EquipmentSlot::Initialize()
	{
		GameObject::Initialize();
	}
	void EquipmentSlot::Update()
	{
		GameObject::Update();

	}
	void EquipmentSlot::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void EquipmentSlot::Render()
	{
		GameObject::Render();
	}

	void EquipmentSlot::SetMaterialName(std::wstring name)
	{
		mMaterName = name;
	}

	void EquipmentSlot::SetMater()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(mMaterName));
	}

	void EquipmentSlot::SetBlank()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}


}

