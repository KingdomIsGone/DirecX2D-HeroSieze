#include "ssItemImage.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

namespace ss
{
	ItemImage::ItemImage(GameObject* parent)
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

	ItemImage::~ItemImage()
	{
	}

	void ItemImage::Initialize()
	{
		GameObject::Initialize();
	}
	void ItemImage::Update()
	{
		GameObject::Update();

		if (mOnList || mOnEquip)
		{
			mRenderer->SetNoRender(false);
			mRenderer->SetMaterial(Resources::Find<Material>(mMaterName));
		}
		else
			SetBlank();

	}
	void ItemImage::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void ItemImage::Render()
	{
		GameObject::Render();
	}

	void ItemImage::SetBlank()
	{
		//mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
		mRenderer->SetNoRender(true);
	}
}