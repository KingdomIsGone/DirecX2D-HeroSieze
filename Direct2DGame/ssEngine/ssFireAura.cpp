#include "ssFireAura.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssTime.h"
#include "ssFireAuraScript.h"

namespace ss
{
	FireAura::FireAura()
		: mDamage(500.0f)
		, mDuration(6.5f)
	{
		SetName(L"FireAura");
		mMScript = AddComponent<FireAuraScript>();

		mTransform = GetComponent<Transform>();

		//콜라이더 세팅
		GetComponent<Transform>()->SetScale(1.3f, 1.3f, 1.0f);
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::Projectile);
		collider->SetSize(Vector2(0.25f, 0.25f));
		collider->SetCenter(Vector2(0.00f, -0.0f));

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"EffectAnimationMaterial"));

		mAnimator = AddComponent<Animator>();

		std::shared_ptr<Texture> FireAuraTex
			= Resources::Load<Texture>(L"FireAuraTex", L"..\\Resources\\Texture\\Skill\\FireAura\\FireAura.png");
		mAnimator->Create(L"FireAura", FireAuraTex, Vector2(0.0f, 0.0f), Vector2(85.f, 85.f), 15);
	

		mTransform->SetScale(Vector3(6.f, 6.f, 1.0));

		mAnimator->PlayAnimation(L"FireAura", true);
	}
	FireAura::~FireAura()
	{
	}
	void FireAura::Initialize()
	{
		GameObject::Initialize();
	}
	void FireAura::Update()
	{
		GameObject::Update();

		mDuration -= 1.f * Time::DeltaTime();

		if (mDuration <= 0.f)
			SetState(eState::Dead);

		

	}
	void FireAura::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void FireAura::Render()
	{
		GameObject::Render();
	}
}