#include "ssMagicRobe.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssSceneManager.h"
#include "Inventory.h"

namespace ss
{
	MagicRobe::MagicRobe()
	{
		SetMaterialName(L"MagicRobeMater");
		SetItemKind(eItemKind::Armor);
		SetItemGrade(eItemGrade::Magic);
		SetItemState(eItemState::Field);
		SetImageOn(true);
		wchar_t itemName[20] = L"MagicRobe";
		SetItemName(itemName);
		wchar_t itemText[20] = L"방어력 20, 지능 10";
		SetItemText(itemText);

		mTransform = GetComponent<Transform>();
		mPos = mTransform->GetPosition();

		mRenderer = GetComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"MagicRobeMater"));

		mCollider = GetComponent<Collider2D>();
	}
	MagicRobe::~MagicRobe()
	{
	}
	void MagicRobe::Initialize()
	{
		GameObject::Initialize();
	}
	void MagicRobe::Update()
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
			mRenderer->SetMaterial(Resources::Find<Material>(L"MagicRobeMater"));
		else
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	void MagicRobe::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MagicRobe::Render()
	{
		GameObject::Render();
	}
	void MagicRobe::OnCollisionEnter(Collider2D* other)
	{
	}
	void MagicRobe::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				MagicRobe* hat = new MagicRobe();
				hat->SetItemState(eItemState::Inventory);
				hat->SetImageOn(false);
				Inventory::PushbackItem(hat);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::Inventory, hat);
				this->SetState(eState::Dead);
			}
		}
	}
	void MagicRobe::OnCollisionExit(Collider2D* other)
	{
	}
}

