#include "ssItemBackground.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

namespace ss
{
	ItemBackground::ItemBackground(GameObject* obj)
	{
		SetParent(obj);
		mTransform = GetComponent<Transform>();
		Vector3 pos = mTransform->GetPosition();
		pos.z -= 0.12f;
		mTransform->SetPosition(pos);
		mTransform->SetScale(Vector3(0.5f, 0.5f, 1.f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));

	}

	ItemBackground::~ItemBackground()
	{
	}

	void ItemBackground::Initialize()
	{
		GameObject::Initialize();
	}
	void ItemBackground::Update()
	{
		GameObject::Update();

		if (mItemIn)
		{
			switch (mGrade)
			{
			case ss::ItemBackground::eGrade::Normal:
				SetMaterNormal();
				break;
			case ss::ItemBackground::eGrade::Magic:
				SetMaterMagic();
				break;
			case ss::ItemBackground::eGrade::Legend:
				SetMaterLegend();
				break;
			default:
				break;
			}
		}
		else
			SetBlank();

	}
	void ItemBackground::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void ItemBackground::Render()
	{
		GameObject::Render();
	}

	void ItemBackground::SetMaterNormal()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"ItemBackNormalMater"));
	}

	void ItemBackground::SetMaterMagic()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"ItemBackMagicMater"));
	}

	void ItemBackground::SetMaterLegend()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"ItemBackLegendMater"));
	}

	void ItemBackground::SetBlank()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
}

