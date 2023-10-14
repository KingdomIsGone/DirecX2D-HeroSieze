#include "ssLightBall.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"
#include "ssDamageScript.h"

namespace ss
{
	float LightBall::mDamage = 200.0f;

	LightBall::LightBall(e4Direction dir)
		: mDeleteTime(0.0f)
		, mSpeed(3.0f)
	{
		SetName(L"LightBall");
		AddComponent<DamageScript>();

		mDir = dir;
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.8f, 1.8f, 1.0f));

		Animator* at = AddComponent<Animator>();
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> LightBallTex
			= Resources::Load<Texture>(L"LightBallTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\LightBall.png");

		at->Create(L"LightBall", LightBallTex, Vector2(0.0f, 0.0f), Vector2(73.f, 65.0f), 6);
		at->PlayAnimation(L"LightBall", true);

		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Projectile);
		mCollider->SetSize(Vector2(0.15f, 0.15f));
	}
	LightBall::~LightBall()
	{
	}
	void LightBall::Initialize()
	{
		GameObject::Initialize();
	}
	void LightBall::Update()
	{
		GameObject::Update();

		Vector3 Pos = mTransform->GetPosition();

		switch (mDir)
		{
		case ss::enums::e4Direction::Up:
			Pos.y += mSpeed * Time::DeltaTime();
			break;
		case ss::enums::e4Direction::Down:
			Pos.y -= mSpeed * Time::DeltaTime();
			break;
		case ss::enums::e4Direction::Right:
			Pos.x += mSpeed * Time::DeltaTime();
			break;
		case ss::enums::e4Direction::Left:
			Pos.x -= mSpeed * Time::DeltaTime();
			break;
		default:
			break;
		}
		mTransform->SetPosition(Pos);
		
	}

	void LightBall::LateUpdate()
	{
		GameObject::LateUpdate();

		mDeleteTime += Time::DeltaTime();

		if (mDeleteTime > 7.0f)
			SetState(eState::Dead);
	}
	void LightBall::Render()
	{
		GameObject::Render();
	}
}
