#include "ssChargedBolt.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"
#include "ssDamageScript.h"

namespace ss
{
	float ChargedBolt::mDamage = 200.0f;
	ChargedBolt::ChargedBolt(bool isVertical)
		: mDeleteTime(0.0f)
		, mSpeed(2.0f)
		, mWaitTime(2.5f)
	{
		SetName(L"ChargedBolt");
		mbIsVertical = isVertical;
		AddComponent<DamageScript>();

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.8f, 1.8f, 1.0f));

		Animator* at = AddComponent<Animator>();
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> ChargedBoltTex
			= Resources::Load<Texture>(L"ChargedBoltTex", L"..\\Resources\\Texture\\Monster\\Anubis\\ChargedBolt29294.png");

		at->Create(L"ChargedBolt", ChargedBoltTex, Vector2(0.0f, 0.0f), Vector2(29.0f, 29.0f), 4);
		at->PlayAnimation(L"ChargedBolt", true);

		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Projectile);
		mCollider->SetSize(Vector2(0.15f, 0.15f));
	}
	ChargedBolt::~ChargedBolt()
	{
	}
	void ChargedBolt::Initialize()
	{
		GameObject::Initialize();
	}
	void ChargedBolt::Update()
	{
		GameObject::Update();

		mWaitTime -= Time::DeltaTime();

		if (mWaitTime <= 0.0f)
		{
			Vector3 Pos = mTransform->GetPosition();

			if (mbIsVertical)
				Pos.x += mSpeed * Time::DeltaTime();
			else
				Pos.y -= mSpeed * Time::DeltaTime();

			mTransform->SetPosition(Pos);
		}
	}

	void ChargedBolt::LateUpdate()
	{
		GameObject::LateUpdate();

		mDeleteTime += Time::DeltaTime();

		if (mDeleteTime > 7.0f && mForInstance == false)
			SetState(eState::Dead);
	}
	void ChargedBolt::Render()
	{
		GameObject::Render();
	}
}
