#include "ssPortal.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"
#include "ssCollider2D.h"
#include "ssDoorScript.h"

namespace ss
{
	Portal::Portal()
	{
		SetName(L"Portal");
		AddComponent<DoorScript>();

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.2f, 1.2f, 1.0f));

		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Item);
		mCollider->SetSize(Vector2(0.2f, 0.4f));

		Animator* animator = AddComponent<Animator>();
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> PortalTex
			= Resources::Load<Texture>(L"PortalTex", L"..\\Resources\\Texture\\MapObject\\Portal.png");
		animator->Create(L"Portal", PortalTex, Vector2(0.0f, 0.0f), Vector2(68.0f, 88.0f), 15);
		animator->PlayAnimation(L"Portal", true);
	}

	Portal::~Portal()
	{
	}

	void Portal::Initialize()
	{
		GameObject::Initialize();
	}

	void Portal::Update()
	{
		GameObject::Update();
	}

	void Portal::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Portal::Render()
	{
		GameObject::Render();
	}
}
