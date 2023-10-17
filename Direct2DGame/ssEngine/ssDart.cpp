#include "ssDart.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"
#include "ssCollider2D.h"
#include "ssDartScript.h"

namespace ss
{
	Dart::Dart(float Degree)
		: mDeleteTime(0.0f)
	{
		AddComponent<DartScript>();
		SetName(L"Dart");

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.2f, 1.2f, 1.0f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> DartTex
			= Resources::Load<Texture>(L"DartTex", L"..\\Resources\\Texture\\Monster\\TreeMon\\Tribal_Doll_Dart_spr.png");

		Animator* at = AddComponent<Animator>();
		at->Create(L"Dart", DartTex, Vector2(0.0f, 0.0f), Vector2(24.0f, 3.0f), 1);
		at->PlayAnimation(L"Dart", false);

		mDirVector = DegreeToVector(Degree);

		Degree /= 56.25f;
		GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, Degree));
		//degree 1.6f당 90도 회전

		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Projectile);
		mCollider->SetSize(Vector2(0.2f, 0.1f));
	}

	Dart::~Dart()
	{
	}

	void Dart::Initialize()
	{
		GameObject::Initialize();
	}

	void Dart::Update()
	{
		GameObject::Update();

		Vector3 pos = mTransform->GetPosition();
		pos.x += mDirVector.x * 2.0f * Time::DeltaTime();
		pos.y += mDirVector.y * 2.0f * Time::DeltaTime();

		mTransform->SetPosition(pos);
	}

	void Dart::LateUpdate()
	{
		GameObject::LateUpdate();

		mDeleteTime += Time::DeltaTime();

		if (mDeleteTime > 5.0f)
			SetState(eState::Dead);
	}

	void Dart::Render()
	{
		GameObject::Render();
	}
}
