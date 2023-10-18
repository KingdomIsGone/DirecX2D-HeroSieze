#include "ssDesertDoor.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"
#include "ssCollider2D.h"
#include "ssDoorScript.h"

namespace ss
{
	DesertDoor::DesertDoor()
	{
		SetName(L"DesertDoor");
		AddComponent<DoorScript>();

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.2f, 1.2f, 1.0f));


		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Item);
		mCollider->SetSize(Vector2(0.2f, 0.1f));
	}

	DesertDoor::~DesertDoor()
	{
	}

	void DesertDoor::Initialize()
	{
		GameObject::Initialize();
	}

	void DesertDoor::Update()
	{
		GameObject::Update();
	}

	void DesertDoor::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void DesertDoor::Render()
	{
		GameObject::Render();
	}
}