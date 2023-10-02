#include "ssEquipIndicator.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

namespace ss
{
	EquipIndicator::EquipIndicator(GameObject* parent)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();
		Vector3 pos = mTransform->GetPosition();
		pos.z -= 0.13f;
		mTransform->SetPosition(pos);
		mTransform->SetScale(Vector3(0.3f, 0.3f, 1.f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));

	}

	EquipIndicator::~EquipIndicator()
	{
	}

	void EquipIndicator::Initialize()
	{
		GameObject::Initialize();
	}
	void EquipIndicator::Update()
	{
		GameObject::Update();

		if (mSelected)
		{
			mRenderer->SetNoRender(false);
			mRenderer->SetMaterial(Resources::Find<Material>(L"EquipSelectMater"));
		}
		else
			SetBlank();

	}
	void EquipIndicator::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void EquipIndicator::Render()
	{
		GameObject::Render();
	}

	void EquipIndicator::SetBlank()
	{
		//mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
		mRenderer->SetNoRender(true);
	}
}
