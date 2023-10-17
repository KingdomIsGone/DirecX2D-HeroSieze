#include "ssMagicBall.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"
#include "ssCollider2D.h"
#include "ssMagicBallScript.h"

namespace ss
{
	MagicBall::MagicBall(float Degree)
		: mDeleteTime(0.0f)
	{
		AddComponent<MagicBallScript>();
		SetName(L"MagicBall");

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.2f, 1.2f, 1.0f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> MagicBallTex
			= Resources::Load<Texture>(L"MagicBallTex", L"..\\Resources\\Texture\\Monster\\SkeletonMage\\MagicBall.png");

		Animator* at = AddComponent<Animator>();
		at->Create(L"MagicBall", MagicBallTex, Vector2(0.0f, 0.0f), Vector2(48.0f, 19.0f), 4);
		at->PlayAnimation(L"MagicBall", true);

		mDirVector = DegreeToVector(Degree);

		Degree /= 56.25f;
		GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, Degree));
		//degree 1.6f당 90도 회전

		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Projectile);
		mCollider->SetSize(Vector2(0.2f, 0.1f));
	}

	MagicBall::~MagicBall()
	{
	}

	void MagicBall::Initialize()
	{
		GameObject::Initialize();
	}

	void MagicBall::Update()
	{
		GameObject::Update();

		Vector3 pos = mTransform->GetPosition();
		pos.x += mDirVector.x * 2.0f * Time::DeltaTime();
		pos.y += mDirVector.y * 2.0f * Time::DeltaTime();

		mTransform->SetPosition(pos);
	}

	void MagicBall::LateUpdate()
	{
		GameObject::LateUpdate();

		mDeleteTime += Time::DeltaTime();

		if (mDeleteTime > 5.0f)
			SetState(eState::Dead);
	}

	void MagicBall::Render()
	{
		GameObject::Render();
	}
}
