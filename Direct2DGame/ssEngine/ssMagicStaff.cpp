#include "ssMagicStaff.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssSceneManager.h"
#include "Inventory.h"

namespace ss
{
	MagicStaff::MagicStaff()
	{
		SetMaterialName(L"MagicStaffMater");
		SetItemKind(eItemKind::Weapon);
		SetItemGrade(eItemGrade::Magic);
		SetItemState(eItemState::Field);
		SetImageOn(true);

		mTransform = GetComponent<Transform>();
		mPos = mTransform->GetPosition();

		mRenderer = GetComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"MagicStaffMater"));

		mCollider = GetComponent<Collider2D>();
	}
	MagicStaff::~MagicStaff()
	{
	}
	void MagicStaff::Initialize()
	{
		GameObject::Initialize();
	}
	void MagicStaff::Update()
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
			mRenderer->SetMaterial(Resources::Find<Material>(L"MagicStaffMater"));
		else
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	void MagicStaff::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MagicStaff::Render()
	{
		GameObject::Render();
	}
	void MagicStaff::OnCollisionEnter(Collider2D* other)
	{
	}
	void MagicStaff::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				MagicStaff* staff = new MagicStaff();
				staff->SetItemState(eItemState::Inventory);
				staff->SetImageOn(false);
				Inventory::PushbackItem(staff);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::Inventory, staff);
				this->SetState(eState::Dead);
			}
		}
	}
	void MagicStaff::OnCollisionExit(Collider2D* other)
	{
	}
}
