#include "ssLegendStaff1.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssSceneManager.h"
#include "Inventory.h"

namespace ss
{
	LegendStaff1::LegendStaff1()
	{
		SetMaterialName(L"LegendStaff1Mater");
		SetItemKind(eKind::Weapon);
		SetItemGrade(eItemGrade::Legend);
		SetItemState(eItemState::Field);
		SetImageOn(true);

		mTransform = GetComponent<Transform>();
		mPos = mTransform->GetPosition();

		mRenderer = GetComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"LegendStaff1Mater"));

		mCollider = GetComponent<Collider2D>();
	}
	LegendStaff1::~LegendStaff1()
	{
	}
	void LegendStaff1::Initialize()
	{
		GameObject::Initialize();
	}
	void LegendStaff1::Update()
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

		if(GetImageOn())
			mRenderer->SetMaterial(Resources::Find<Material>(L"LegendStaff1Mater"));
		else
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	void LegendStaff1::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void LegendStaff1::Render()
	{
		GameObject::Render();
	}
	void LegendStaff1::OnCollisionEnter(Collider2D* other)
	{
	}
	void LegendStaff1::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				LegendStaff1* staff = new LegendStaff1();
				staff->SetItemState(eItemState::Inventory);
				staff->SetImageOn(false);
				Inventory::PushbackItem(staff);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::Inventory, staff);
				this->SetState(eState::Dead);
			}
		}
	}
	void LegendStaff1::OnCollisionExit(Collider2D* other)
	{
	}
}
