#include "ssEnt.h"

#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssEntScript.h"
#include "ssEnemyHpBar.h"
#include "ssEnemyHpBarFill.h"

namespace ss
{
	Ent::Ent()
		: mCurHp(1000.0f)
		, mPrevHp(1000.0f)
	{
		SetName(L"Ent");
		mMScript = AddComponent<EntScript>();

		//콜라이더 세팅
		GetComponent<Transform>()->SetScale(1.3f, 1.3f, 1.0f);
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::NormalMonster);
		collider->SetSize(Vector2(0.24f, 0.34f));
		collider->SetCenter(Vector2(-0.00f, -0.0f));

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		Animator* at = AddComponent<Animator>();

		//Move Ani
		std::shared_ptr<Texture> Ent_UpTex
			= Resources::Load<Texture>(L"Ent_UpTex", L"..\\Resources\\Texture\\Monster\\Ent\\EntWalkUp.png");
		at->Create(L"Ent_Up", Ent_UpTex, Vector2(0.0f, 0.0f), Vector2(76.0f, 91.0f), 8);

		std::shared_ptr<Texture> Ent_DownTex
			= Resources::Load<Texture>(L"Ent_DownTex", L"..\\Resources\\Texture\\Monster\\Ent\\EntWalkDown.png");
		at->Create(L"Ent_Down", Ent_DownTex, Vector2(0.0f, 0.0f), Vector2(75.0f, 89.0f), 8);

		std::shared_ptr<Texture> Ent_LeftTex
			= Resources::Load<Texture>(L"Ent_LeftTex", L"..\\Resources\\Texture\\Monster\\Ent\\EntWalkLeft.png");
		at->Create(L"Ent_Left", Ent_LeftTex, Vector2(0.0f, 0.0f), Vector2(63.0f, 87.0f), 8);

		std::shared_ptr<Texture> Ent_RightTex
			= Resources::Load<Texture>(L"Ent_RightTex", L"..\\Resources\\Texture\\Monster\\Ent\\EntWalkRight.png");
		at->Create(L"Ent_Right", Ent_RightTex, Vector2(0.0f, 0.0f), Vector2(63.0f, 87.0f), 8);

		//Attack Ani
		std::shared_ptr<Texture> Ent_AtkRightTex
			= Resources::Load<Texture>(L"Ent_AtkRightTex", L"..\\Resources\\Texture\\Monster\\Ent\\EntAtkRight.png");
		at->Create(L"Ent_AtkRight", Ent_AtkRightTex, Vector2(0.0f, 0.0f), Vector2(79.0f, 92.0f), 8, Vector2(0.01f, 0.f));

		std::shared_ptr<Texture> Ent_AtkLeftTex
			= Resources::Load<Texture>(L"Ent_AtkLeftTex", L"..\\Resources\\Texture\\Monster\\Ent\\EntAtkLeft.png");
		at->Create(L"Ent_AtkLeft", Ent_AtkLeftTex, Vector2(0.0f, 0.0f), Vector2(79.0f, 92.0f), 8, Vector2(-0.01f, 0.f));

		std::shared_ptr<Texture> Ent_AtkUpTex
			= Resources::Load<Texture>(L"Ent_AtkUpTex", L"..\\Resources\\Texture\\Monster\\Ent\\EntAtkUp.png");
		at->Create(L"Ent_AtkUp", Ent_AtkUpTex, Vector2(0.0f, 0.0f), Vector2(81.0f, 88.0f), 8);

		std::shared_ptr<Texture> Ent_AtkDownTex
			= Resources::Load<Texture>(L"Ent_AtkDownTex", L"..\\Resources\\Texture\\Monster\\Ent\\EntAtkDown.png");
		at->Create(L"Ent_AtkDown", Ent_AtkDownTex, Vector2(0.0f, 0.0f), Vector2(78.0f, 113.0f), 8, Vector2(0.f, 0.07f));

		std::shared_ptr<Texture> Ent_IdleTex
			= Resources::Load<Texture>(L"Ent_IdleTex", L"..\\Resources\\Texture\\Monster\\Ent\\EntIdle.png");
		at->Create(L"Ent_Idle", Ent_IdleTex, Vector2(0.0f, 0.0f), Vector2(75.0f, 89.0f), 1);

		at->PlayAnimation(L"Ent_Idle", false);

		//hp바, fill
		mHpBar = new EnemyHpBar();
		mHpBar->SetName(L"enemyHpBar");
		mTransform = GetComponent<Transform>();
		mHpBar->SetOwnerTransform(mTransform);
		mHpBar->SetOffset(0.f, 0.27f);
		mHpBar->GetComponent<Transform>()->SetScale(Vector3(0.6f, 0.1f, 1.f));
		AddOtherGameObject(mHpBar, eLayerType::MonsterUI);

		mHpBarFill = new EnemyHpBarFill();
		mHpBarFill->SetOwnerTransform(mTransform);
		mHpBarFill->SetOffset(0.0f, 0.28f);
		mHpBarFill->SetFullHp(mCurHp);
		mHpBarFill->SetFullScale(0.19f, 0.02f);
		AddOtherGameObject(mHpBarFill, eLayerType::MonsterUI);
	}
	Ent::~Ent()
	{
		mHpBar->SetState(eState::Dead);
		mHpBarFill->SetState(eState::Dead);
	}
	void Ent::Initialize()
	{
		GameObject::Initialize();
	}
	void Ent::Update()
	{
		GameObject::Update();

		mCurHp = mMScript->GetHP();
		if (mCurHp != mPrevHp)
		{
			mHpBarFill->ChangeHP(mCurHp);

			mPrevHp = mCurHp;
		}

	}
	void Ent::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Ent::Render()
	{
		GameObject::Render();
	}
}
