#include "ssFlames.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssTime.h"
#include "ssMeteorScript.h"
#include "ssFlameScript.h"

namespace ss
{
	Flames::Flames()
		: mDamage(80.0f)
		, mDeadTime(5.f)
	{
		SetName(L"Flames");
		mScript = AddComponent<FlameScript>();

		mTransform = GetComponent<Transform>();

		//콜라이더 세팅
		GetComponent<Transform>()->SetScale(1.3f, 1.3f, 1.0f);
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::Projectile);
		collider->SetSize(Vector2(0.8f, 0.55f));
		collider->SetCenter(Vector2(-0.00f, -0.1f));

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		mAnimator = AddComponent<Animator>();

		std::shared_ptr<Texture> FlameTex
			= Resources::Load<Texture>(L"FlameTex", L"..\\Resources\\Texture\\Skill\\Meteor\\Flames.png");
		mAnimator->Create(L"Flame", FlameTex, Vector2(0.0f, 0.0f), Vector2(190.0f, 175.0f), 6);

		mTransform->SetScale(Vector3(1.4f, 1.4f, 1.0));

		mAnimator->PlayAnimation(L"Flame", true);
	}
	Flames::~Flames()
	{
	}
	void Flames::Initialize()
	{
		GameObject::Initialize();
	}
	void Flames::Update()
	{
		GameObject::Update();

		mDeadTime -= Time::DeltaTime();

		
	}
	void Flames::LateUpdate()
	{
		GameObject::LateUpdate();

		if (mDeadTime <= 0.f)
			SetState(eState::Dead);
	}
	void Flames::Render()
	{
		GameObject::Render();
	}
}