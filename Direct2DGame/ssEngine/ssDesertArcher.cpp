#include "ssDesertArcher.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssEnemyHpBar.h"
#include "ssEnemyHpBarFill.h"
#include "ssDesertArcherScript.h"

namespace ss
{
	DesertArcher::DesertArcher()
		: mCurHp(1000.0f)
		, mPrevHp(1000.0f)
	{
		SetName(L"DesertArcher");
		mMScript = AddComponent<DesertArcherScript>();

		//콜라이더 세팅
		GetComponent<Transform>()->SetScale(1.3f, 1.3f, 1.0f);
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::NormalMonster);
		collider->SetSize(Vector2(0.15f, 0.24f));
		collider->SetCenter(Vector2(-0.00f, 0.0f));

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		Animator* at = AddComponent<Animator>();

		//Move Ani
		std::shared_ptr<Texture> ArcherWalkUpTex
			= Resources::Load<Texture>(L"ArcherWalkUpTex", L"..\\Resources\\Texture\\Monster\\DesertArcher\\ArcherWalkUp.png");
		at->Create(L"ArcherWalkUp", ArcherWalkUpTex, Vector2(0.0f, 0.0f), Vector2(25.0f, 53.0f), 8);

		std::shared_ptr<Texture> ArcherWalkDownTex
			= Resources::Load<Texture>(L"ArcherWalkDownTex", L"..\\Resources\\Texture\\Monster\\DesertArcher\\ArcherWalkDown.png");
		at->Create(L"ArcherWalkDown", ArcherWalkDownTex, Vector2(0.0f, 0.0f), Vector2(33.0f, 50.0f), 8);

		std::shared_ptr<Texture> ArcherWalkLeftTex
			= Resources::Load<Texture>(L"ArcherWalkLeftTex", L"..\\Resources\\Texture\\Monster\\DesertArcher\\ArcherWalkLeft.png");
		at->Create(L"ArcherWalkLeft", ArcherWalkLeftTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 50.0f), 8);

		std::shared_ptr<Texture> ArcherWalkRightTex
			= Resources::Load<Texture>(L"ArcherWalkRightTex", L"..\\Resources\\Texture\\Monster\\DesertArcher\\ArcherWalkRight.png");
		at->Create(L"ArcherWalkRight", ArcherWalkRightTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 50.0f), 8);

		//Attack Ani
		std::shared_ptr<Texture> ArcherAtkUpTex
			= Resources::Load<Texture>(L"ArcherAtkUpTex", L"..\\Resources\\Texture\\Monster\\DesertArcher\\ArcherAtkUp.png");
		at->Create(L"ArcherAtkUp", ArcherAtkUpTex, Vector2(0.0f, 0.0f), Vector2(24.0f, 49.0f), 9, Vector2::Zero, 0.12f);

		std::shared_ptr<Texture> ArcherAtkDownTex
			= Resources::Load<Texture>(L"ArcherAtkDownTex", L"..\\Resources\\Texture\\Monster\\DesertArcher\\ArcherAtkDown.png");
		at->Create(L"ArcherAtkDown", ArcherAtkDownTex, Vector2(0.0f, 0.0f), Vector2(32.0f, 47.0f), 10, Vector2::Zero, 0.12f);

		std::shared_ptr<Texture> ArcherAtkRightTex
			= Resources::Load<Texture>(L"ArcherAtkRightTex", L"..\\Resources\\Texture\\Monster\\DesertArcher\\ArcherAtkRight.png");
		at->Create(L"ArcherAtkRight", ArcherAtkRightTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 49.0f), 9, Vector2::Zero, 0.12f);

		std::shared_ptr<Texture> ArcherAtkLeftTex
			= Resources::Load<Texture>(L"ArcherAtkLeftTex", L"..\\Resources\\Texture\\Monster\\DesertArcher\\ArcherAtkLeft.png");
		at->Create(L"ArcherAtkLeft", ArcherAtkLeftTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 49.0f), 9, Vector2::Zero, 0.12f);

		//Idle
		std::shared_ptr<Texture> ArcherIdleTex
			= Resources::Load<Texture>(L"ArcherIdleTex", L"..\\Resources\\Texture\\Monster\\DesertArcher\\ArcherIdle.png");
		at->Create(L"ArcherIdle", ArcherIdleTex, Vector2(0.0f, 0.0f), Vector2(32.0f, 47.0f), 6);

		at->PlayAnimation(L"ArcherIdle", true);


		//hp바, fill
		mHpBar = new EnemyHpBar();
		mHpBar->SetName(L"enemyHpBar");
		mTransform = GetComponent<Transform>();
		mHpBar->SetOwnerTransform(mTransform);
		mHpBar->SetOffset(0.f, 0.25f);
		mHpBar->GetComponent<Transform>()->SetScale(Vector3(0.6f, 0.1f, 1.f));
		AddOtherGameObject(mHpBar, eLayerType::MonsterUI);

		mHpBarFill = new EnemyHpBarFill();
		mHpBarFill->SetOwnerTransform(mTransform);
		mHpBarFill->SetOffset(0.0f, 0.26f);
		mHpBarFill->SetFullHp(mCurHp);
		mHpBarFill->SetFullScale(0.19f, 0.02f);
		AddOtherGameObject(mHpBarFill, eLayerType::MonsterUI);
	}
	DesertArcher::~DesertArcher()
	{
		mHpBar->SetState(eState::Dead);
		mHpBarFill->SetState(eState::Dead);
	}
	void DesertArcher::Initialize()
	{
		GameObject::Initialize();
	}
	void DesertArcher::Update()
	{
		GameObject::Update();

		mCurHp = mMScript->GetHP();
		if (mCurHp != mPrevHp)
		{
			mHpBarFill->ChangeHP(mCurHp);

			mPrevHp = mCurHp;
		}

	}
	void DesertArcher::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DesertArcher::Render()
	{
		GameObject::Render();
	}
}
