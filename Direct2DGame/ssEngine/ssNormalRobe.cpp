#include "ssNormalRobe.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssSceneManager.h"
#include "Inventory.h"

namespace ss
{
	NormalRobe::NormalRobe()
	{
		SetMaterialName(L"NormalRobeMater");
		SetItemKind(eItemKind::Armor);
		SetItemGrade(eItemGrade::Normal);
		SetItemState(eItemState::Field);
		SetImageOn(true);
		wchar_t itemName[20] = L"NormalRobe";
		SetItemName(itemName);
		wchar_t itemText[20] = L"방어력 10, 지능 5";
		SetItemText(itemText);

		mTransform = GetComponent<Transform>();
		mPos = mTransform->GetPosition();

		mRenderer = GetComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"NormalRobeMater"));

		mCollider = GetComponent<Collider2D>();
	}
	NormalRobe::~NormalRobe()
	{
	}
	void NormalRobe::Initialize()
	{
		GameObject::Initialize();
	}
	void NormalRobe::Update()
	{
		GameObject::Update();

		mState = GetItemState();

		switch (mState)
		{
		case ss::Item::eItemState::Inventory:
		{
			mPos.z = -0.14f;
			mTransform->SetPosition(mPos);
		}
		break;
		case ss::Item::eItemState::Field:
		{
			mTransform->SetScale(0.2f, 0.3f, 1.0f);
		}
		break;
		default:
			break;
		}

		if (GetImageOn())
			mRenderer->SetMaterial(Resources::Find<Material>(L"NormalRobeMater"));
		else
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	void NormalRobe::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void NormalRobe::Render()
	{
		GameObject::Render();
	}
	void NormalRobe::OnCollisionEnter(Collider2D* other)
	{
	}
	void NormalRobe::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				NormalRobe* hat = new NormalRobe();
				hat->SetItemState(eItemState::Inventory);
				hat->SetImageOn(false);
				Inventory::PushbackItem(hat);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::Inventory, hat);
				this->SetState(eState::Dead);
			}
		}
	}
	void NormalRobe::OnCollisionExit(Collider2D* other)
	{
	}
}


