#include "ssArrow.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"
#include "ssCollider2D.h"
#include "ssArrowScript.h"

namespace ss
{
	Arrow::Arrow(float Degree)
		: mDeleteTime(0.0f)
	{
		AddComponent<ArrowScript>();
		SetName(L"Arrow");

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.2f, 1.2f, 1.0f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> ArrowTex
			= Resources::Load<Texture>(L"ArrowTex", L"..\\Resources\\Texture\\Monster\\DesertArcher\\Arrows.png");

		Animator* at = AddComponent<Animator>();
		at->Create(L"Arrow", ArrowTex, Vector2(0.0f, 0.0f), Vector2(28.0f, 9.0f), 4);
		at->PlayAnimation(L"Arrow", true);

		mDirVector = DegreeToVector(Degree);

		Degree /= 56.25f;
		GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, Degree));
		//degree 1.6f당 90도 회전

		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Projectile);
		mCollider->SetSize(Vector2(0.2f, 0.1f));
	}

	Arrow::~Arrow()
	{
	}

	void Arrow::Initialize()
	{
		GameObject::Initialize();
	}

	void Arrow::Update()
	{
		GameObject::Update();

		Vector3 pos = mTransform->GetPosition();
		pos.x += mDirVector.x * 3.0f * Time::DeltaTime();
		pos.y += mDirVector.y * 3.0f * Time::DeltaTime();

		mTransform->SetPosition(pos);
	}

	void Arrow::LateUpdate()
	{
		GameObject::LateUpdate();

		mDeleteTime += Time::DeltaTime();

		if (mDeleteTime > 5.0f)
			SetState(eState::Dead);
	}

	void Arrow::Render()
	{
		GameObject::Render();
	}
}
