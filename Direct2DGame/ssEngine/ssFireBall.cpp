#include "ssFireBall.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"
#include "ssCollider2D.h"

namespace ss
{
	FireBall::FireBall(float Degree)
		: mDeleteTime(0.0f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.2f, 1.2f, 1.0f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> FireBallTex
			= Resources::Load<Texture>(L"FireBallTex", L"..\\Resources\\Texture\\Projectile\\FireBall.png");

		Animator* at = AddComponent<Animator>();
		at->Create(L"FireBall", FireBallTex, Vector2(0.0f, 0.0f), Vector2(48.0f, 19.0f), 5);
		at->PlayAnimation(L"FireBall", true);

		mDirVector = DegreeToVector(Degree);

		Degree /= 56.25f;
		GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, Degree));
		//degree 1.6f당 90도 회전
		
		mCollider = AddComponent<Collider2D>();
		mCollider->SetSize(Vector2(0.2f, 0.1f));
	}

	FireBall::~FireBall()
	{
	}

	void FireBall::Initialize()
	{
		GameObject::Initialize();
	}

	void FireBall::Update()
	{
		GameObject::Update();

		Vector3 pos = mTransform->GetPosition();
		pos.x += mDirVector.x * 3.0f * Time::DeltaTime();
		pos.y += mDirVector.y * 3.0f * Time::DeltaTime();

		mTransform->SetPosition(pos);
	}

	void FireBall::LateUpdate()
	{
		GameObject::LateUpdate();

		mDeleteTime += Time::DeltaTime();

		if (mDeleteTime > 5.0f)
			SetState(eState::Dead);
	}

	void FireBall::Render()
	{
		GameObject::Render();
	}
}