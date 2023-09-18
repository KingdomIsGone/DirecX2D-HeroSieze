#include "ssItem.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssItemBackground.h"
#include "ssCollider2D.h"

namespace ss
{
	Item::Item()
	{
		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		Collider2D* col = AddComponent<Collider2D>();
		col->SetCollideType(eCollideType::Item);
	}

	Item::~Item()
	{
	}

	void Item::Initialize()
	{
		GameObject::Initialize();
	}
	void Item::Update()
	{
		GameObject::Update();
	}
	void Item::LateUpdate()
	{
		GameObject::LateUpdate();

		
	}

	void Item::Render()
	{
		GameObject::Render();
	}

	void Item::SetMaterialName(std::wstring name)
	{
		mMaterName = name;
	}

	void Item::OnCollisionEnter(Collider2D* other)
	{
	}

	void Item::OnCollisionStay(Collider2D* other)
	{
	}

	void Item::OnCollisionExit(Collider2D* other)
	{
	}
}
