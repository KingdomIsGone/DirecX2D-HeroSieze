#include "ssChainLightening.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"
#include "ssDamageScript.h"

namespace ss
{
	float ChainLightening::mDamage = 200.0f;

	ChainLightening::ChainLightening()
		: mDeleteTime(0.0f)
		, mSpeed(2.0f)
	{
		SetName(L"ChainLightening");
		AddComponent<DamageScript>();

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.8f, 1.f, 1.0f));
		mTransform->SetRotation(Vector3(0.0f, 0.0f, 4.7f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> ChainLighteningTex
			= Resources::Load<Texture>(L"ChainLighteningTex", L"..\\Resources\\Texture\\Monster\\Anubis\\ChainLightening382_34_4.png");

		Animator* mAnimator = AddComponent<Animator>();
		mAnimator->Create(L"ChainLightening", ChainLighteningTex, Vector2(0.0f, 0.0f), Vector2(382.0f, 34.0f), 4);
		mAnimator->PlayAnimation(L"ChainLightening", true);

		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Projectile);
		mCollider->SetSize(Vector2(0.2f, 0.17f));
		mCollider->SetCenter(Vector2(0.0f, -0.71f));

	}
	ChainLightening::~ChainLightening()
	{
	}
	void ChainLightening::Initialize()
	{
		GameObject::Initialize();
	}
	void ChainLightening::Update()
	{
		GameObject::Update();

		
	}

	void ChainLightening::LateUpdate()
	{
		GameObject::LateUpdate();

		mDeleteTime += Time::DeltaTime();
		
		if (mDeleteTime > 2.0f)
			SetState(eState::Dead);
	}

	void ChainLightening::Render()
	{
		GameObject::Render();
	}
}
