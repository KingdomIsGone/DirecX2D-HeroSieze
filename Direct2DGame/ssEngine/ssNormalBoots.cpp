#include "ssNormalBoots.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssSceneManager.h"
#include "Inventory.h"

namespace ss
{
	NormalBoots::NormalBoots()
	{
		SetMaterialName(L"NormalBootsMater");
		SetItemKind(eItemKind::Shoes);
		SetItemGrade(eItemGrade::Normal);
		SetItemState(eItemState::Field);
		SetImageOn(true);
		wchar_t itemName[20] = L"NormalBoots";
		SetItemName(itemName);
		wchar_t itemText[20] = L"방어력 10 스피드 5";
		SetItemText(itemText);

		mTransform = GetComponent<Transform>();
		mPos = mTransform->GetPosition();

		mRenderer = GetComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"NormalBootsMater"));

		mCollider = GetComponent<Collider2D>();
	}
	NormalBoots::~NormalBoots()
	{
	}
	void NormalBoots::Initialize()
	{
		GameObject::Initialize();
	}
	void NormalBoots::Update()
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
			mRenderer->SetMaterial(Resources::Find<Material>(L"NormalBootsMater"));
		else
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	void NormalBoots::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void NormalBoots::Render()
	{
		GameObject::Render();
	}
	void NormalBoots::OnCollisionEnter(Collider2D* other)
	{
	}
	void NormalBoots::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				NormalBoots* hat = new NormalBoots();
				hat->SetItemState(eItemState::Inventory);
				hat->SetImageOn(false);
				Inventory::PushbackItem(hat);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::Inventory, hat);
				this->SetState(eState::Dead);
			}
		}
	}
	void NormalBoots::OnCollisionExit(Collider2D* other)
	{
	}
}

