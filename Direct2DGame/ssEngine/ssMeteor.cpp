#include "ssMeteor.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssTime.h"
#include "ssMeteorScript.h"
#include "ssSceneManager.h"
#include "ssFlames.h"

namespace ss
{
	Meteor::Meteor()
		: mDamage(500.0f)
		, mDelayTime(2.5f)
		, mStage(0)
	{
		SetName(L"Meteor");
		mMScript = AddComponent<MeteorScript>();

		mTransform = GetComponent<Transform>();

		//콜라이더 세팅
		GetComponent<Transform>()->SetScale(1.3f, 1.3f, 1.0f);
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::Projectile);
		collider->SetSize(Vector2(0.25f, 0.25f));
		collider->SetCenter(Vector2(-0.00f, -0.1f));

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		mAnimator = AddComponent<Animator>();

		std::shared_ptr<Texture> MetorTex
			= Resources::Load<Texture>(L"MetorTex", L"..\\Resources\\Texture\\Skill\\Meteor\\Metor35598.png");
		mAnimator->Create(L"Meteor", MetorTex, Vector2(0.0f, 0.0f), Vector2(35.0f, 59.0f), 8);
		std::shared_ptr<Texture> MoltenNovaTex
			= Resources::Load<Texture>(L"MoltenNovaTex", L"..\\Resources\\Texture\\Skill\\Meteor\\MoltenNova46339.png");
		mAnimator->Create(L"MoltenNova", MoltenNovaTex, Vector2(0.0f, 0.0f), Vector2(46.0f, 33.0f), 9);
		std::shared_ptr<Texture> MeteorExplodeTex
			= Resources::Load<Texture>(L"MeteorExplodeTex", L"..\\Resources\\Texture\\Skill\\Meteor\\Explode10010013.png");
		mAnimator->Create(L"MeteorExplode", MeteorExplodeTex, Vector2(0.0f, 0.0f), Vector2(100.0f, 100.0f), 13);

		mTransform->SetScale(Vector3(3.5f, 3.5f, 1.0));
		

		mAnimator->PlayAnimation(L"MoltenNova", true);
	}
	Meteor::~Meteor()
	{
	}
	void Meteor::Initialize()
	{
		GameObject::Initialize();
	}
	void Meteor::Update()
	{
		GameObject::Update();
		mPos = mTransform->GetPosition();

		mDelayTime -= Time::DeltaTime();

		if (mDelayTime <= 0.0f && mStage == 0)
		{
			mTransform->SetScale(Vector3(2.5f, 2.5f, 1.0));
			mAnimator->PlayAnimation(L"Meteor", true);
			mStage++;
			mTargetY = mPos.y + 0.1f;
			mPos.y += 2.5f;
			mPos.z = 0.9f;
			mTransform->SetPosition(mPos);
		}
		else if (mStage == 1)
		{
			Vector3 pos = mTransform->GetPosition();
			pos.y -= 3.0f * Time::DeltaTime();
			mTransform->SetPosition(pos);

			if (pos.y <= mTargetY)
				mStage++;
		}
		else if (mStage == 2)
		{
			mAnimator->PlayAnimation(L"MeteorExplode", false);
			mMScript->SetDamageActivate();

			Flames* flame = new Flames();
			Vector3 pos = mTransform->GetPosition();
			pos.z = 1.1f;
			flame->GetComponent<Transform>()->SetPosition(pos);

			SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, flame);

			if (mAnimator->GetActiveAnimation()->IsComplete())
			{
				SetState(eState::Dead);
			}
		}

	}
	void Meteor::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Meteor::Render()
	{
		GameObject::Render();
	}
}