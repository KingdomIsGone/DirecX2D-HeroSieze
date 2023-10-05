#include "ssMagicHat.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssSceneManager.h"
#include "Inventory.h"

namespace ss
{
	MagicHat::MagicHat()
	{
		SetMaterialName(L"MagicHatMater");
		SetItemKind(eItemKind::Helmet);
		SetItemGrade(eItemGrade::Magic);
		SetItemState(eItemState::Field);
		SetImageOn(true);
		wchar_t itemName[20] = L"MagicHat";
		SetItemName(itemName);
		wchar_t itemText[20] = L"방어력 20, 지능 10";
		SetItemText(itemText);

		mTransform = GetComponent<Transform>();
		mPos = mTransform->GetPosition();

		mRenderer = GetComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"MagicHatMater"));

		mCollider = GetComponent<Collider2D>();
	}
	MagicHat::~MagicHat()
	{
	}
	void MagicHat::Initialize()
	{
		GameObject::Initialize();
	}
	void MagicHat::Update()
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
			mRenderer->SetMaterial(Resources::Find<Material>(L"MagicHatMater"));
		else
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	void MagicHat::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MagicHat::Render()
	{
		GameObject::Render();
	}
	void MagicHat::OnCollisionEnter(Collider2D* other)
	{
	}
	void MagicHat::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				MagicHat* hat = new MagicHat();
				hat->SetItemState(eItemState::Inventory);
				hat->SetImageOn(false);
				Inventory::PushbackItem(hat);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::Inventory, hat);
				this->SetState(eState::Dead);
			}
		}
	}
	void MagicHat::OnCollisionExit(Collider2D* other)
	{
	}
}

