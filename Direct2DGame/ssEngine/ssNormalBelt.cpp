#include "ssNormalBelt.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssSceneManager.h"
#include "Inventory.h"

namespace ss
{
	NormalBelt::NormalBelt()
	{
		SetMaterialName(L"NormalBeltMater");
		SetItemKind(eItemKind::Belt);
		SetItemGrade(eItemGrade::Normal);
		SetItemState(eItemState::Field);
		SetImageOn(true);
		wchar_t itemName[20] = L"NormalBelt";
		SetItemName(itemName);
		wchar_t itemText[20] = L"¹æ¾î·Â 5";
		SetItemText(itemText);

		mTransform = GetComponent<Transform>();
		mPos = mTransform->GetPosition();

		mRenderer = GetComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"NormalBeltMater"));

		mCollider = GetComponent<Collider2D>();
	}
	NormalBelt::~NormalBelt()
	{
	}
	void NormalBelt::Initialize()
	{
		GameObject::Initialize();
	}
	void NormalBelt::Update()
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
			mRenderer->SetMaterial(Resources::Find<Material>(L"NormalBeltMater"));
		else
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	void NormalBelt::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void NormalBelt::Render()
	{
		GameObject::Render();
	}
	void NormalBelt::OnCollisionEnter(Collider2D* other)
	{
	}
	void NormalBelt::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				NormalBelt* hat = new NormalBelt();
				hat->SetItemState(eItemState::Inventory);
				hat->SetImageOn(false);
				Inventory::PushbackItem(hat);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::Inventory, hat);
				this->SetState(eState::Dead);
			}
		}
	}
	void NormalBelt::OnCollisionExit(Collider2D* other)
	{
	}
}

