#include "ssNormalStaff.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssSceneManager.h"
#include "Inventory.h"

namespace ss
{
	NormalStaff::NormalStaff()
	{
		SetMaterialName(L"NormalStaffMater");
		SetItemKind(eItemKind::Weapon);
		SetItemGrade(eItemGrade::Normal);
		SetItemState(eItemState::Field);
		SetImageOn(true);
		wchar_t itemName[20] = L"NormalStaff";
		SetItemName(itemName);
		wchar_t itemText[20] = L"°ø°Ý·Â: 50";
		SetItemText(itemText);


		mTransform = GetComponent<Transform>();
		mPos = mTransform->GetPosition();

		mRenderer = GetComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"NormalStaffMater"));

		mCollider = GetComponent<Collider2D>();
	}
	NormalStaff::~NormalStaff()
	{
	}
	void NormalStaff::Initialize()
	{
		GameObject::Initialize();
	}
	void NormalStaff::Update()
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
			mRenderer->SetMaterial(Resources::Find<Material>(L"NormalStaffMater"));
		else
			mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	void NormalStaff::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void NormalStaff::Render()
	{
		GameObject::Render();
	}
	void NormalStaff::OnCollisionEnter(Collider2D* other)
	{
	}
	void NormalStaff::OnCollisionStay(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			if (Input::GetKeyDown(eKeyCode::F))
			{
				NormalStaff* staff = new NormalStaff();
				staff->SetItemState(eItemState::Inventory);
				staff->SetImageOn(false);
				Inventory::PushbackItem(staff);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::Inventory, staff);
				this->SetState(eState::Dead);
			}
		}
	}
	void NormalStaff::OnCollisionExit(Collider2D* other)
	{
	}
}
