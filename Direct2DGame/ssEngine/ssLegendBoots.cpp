#include "ssLegendBoots.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssSceneManager.h"
#include "Inventory.h"

namespace ss
{
	LegendBoots::LegendBoots()
	{
		SetMaterialName(L"LegendBootsMater");
		SetItemKind(eItemKind::Shoes);
		SetItemGrade(eItemGrade::Legend);
		SetItemState(eItemState::Field);
		SetImageOn(true);
		wchar_t itemName[20] = L"LegendBoots";
		SetItemName(itemName);
		wchar_t itemText[20] = L"방어력 30 스피드 15";
		SetItemText(itemText);

		mTransform = GetComponent<Transform>();
		mPos = mTransform->GetPosition();

		mRenderer = GetComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"LegendBootsMater"));

		mCollider = GetComponent<Collider2D>();
	}
	LegendBoots::~LegendBoots()
	{
	}
	void LegendBoots::Initialize()
	{
		GameObject::Initialize();
	}
	void LegendBoots::Update()
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
			mRenderer->SetMaterial(Resources::Find<Material>(L"LegendBootsMater"));
		else
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	void LegendBoots::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void LegendBoots::Render()
	{
		GameObject::Render();
	}
	void LegendBoots::OnCollisionEnter(Collider2D* other)
	{
	}
	void LegendBoots::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				LegendBoots* hat = new LegendBoots();
				hat->SetItemState(eItemState::Inventory);
				hat->SetImageOn(false);
				Inventory::PushbackItem(hat);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::Inventory, hat);
				this->SetState(eState::Dead);
			}
		}
	}
	void LegendBoots::OnCollisionExit(Collider2D* other)
	{
	}
}

