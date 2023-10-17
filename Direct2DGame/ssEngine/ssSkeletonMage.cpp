#include "ssSkeletonMage.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssEnemyHpBar.h"
#include "ssEnemyHpBarFill.h"
#include "ssSkeletonMageScript.h"

namespace ss
{
	SkeletonMage::SkeletonMage()
		: mCurHp(1000.0f)
		, mPrevHp(1000.0f)
	{
		SetName(L"SkeletonMage");
		mMScript = AddComponent<SkeletonMageScript>();

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
		std::shared_ptr<Texture> SkMageWalkUpTex
			= Resources::Load<Texture>(L"SkMageWalkUpTex", L"..\\Resources\\Texture\\Monster\\SkeletonMage\\SkMageUp.png");
		at->Create(L"SkMageWalkUp", SkMageWalkUpTex, Vector2(0.0f, 0.0f), Vector2(25.0f, 42.0f), 8);

		std::shared_ptr<Texture> SkMageWalkDownTex
			= Resources::Load<Texture>(L"SkMageWalkDownTex", L"..\\Resources\\Texture\\Monster\\SkeletonMage\\SkMageDown.png");
		at->Create(L"SkMageWalkDown", SkMageWalkDownTex, Vector2(0.0f, 0.0f), Vector2(25.0f, 42.0f), 8);

		std::shared_ptr<Texture> SkMageWalkLeftTex
			= Resources::Load<Texture>(L"SkMageWalkLeftTex", L"..\\Resources\\Texture\\Monster\\SkeletonMage\\SkMageLeft.png");
		at->Create(L"SkMageWalkLeft", SkMageWalkLeftTex, Vector2(0.0f, 0.0f), Vector2(26.0f, 43.0f), 8);

		std::shared_ptr<Texture> SkMageWalkRightTex
			= Resources::Load<Texture>(L"SkMageWalkRightTex", L"..\\Resources\\Texture\\Monster\\SkeletonMage\\SkMageRight.png");
		at->Create(L"SkMageWalkRight", SkMageWalkRightTex, Vector2(0.0f, 0.0f), Vector2(26.0f, 43.0f), 8);

		//Attack Ani
		std::shared_ptr<Texture> SkMageAtkUpTex
			= Resources::Load<Texture>(L"SkMageAtkUpTex", L"..\\Resources\\Texture\\Monster\\SkeletonMage\\SkMageAtkUp.png");
		at->Create(L"SkMageAtkUp", SkMageAtkUpTex, Vector2(0.0f, 0.0f), Vector2(25.0f, 57.0f), 8, Vector2::Zero, 0.12f);

		std::shared_ptr<Texture> SkMageAtkDownTex
			= Resources::Load<Texture>(L"SkMageAtkDownTex", L"..\\Resources\\Texture\\Monster\\SkeletonMage\\SkMageAtkDown.png");
		at->Create(L"SkMageAtkDown", SkMageAtkDownTex, Vector2(0.0f, 0.0f), Vector2(25.0f, 53.0f), 8, Vector2::Zero, 0.12f);

		std::shared_ptr<Texture> SkMageAtkLeftTex
			= Resources::Load<Texture>(L"SkMageAtkLeftTex", L"..\\Resources\\Texture\\Monster\\SkeletonMage\\SkMageAtkLeft.png");
		at->Create(L"SkMageAtkLeft", SkMageAtkLeftTex, Vector2(0.0f, 0.0f), Vector2(47.0f, 41.0f), 8, Vector2::Zero, 0.12f);

		std::shared_ptr<Texture> SkMageAtkRightTex
			= Resources::Load<Texture>(L"SkMageAtkRightTex", L"..\\Resources\\Texture\\Monster\\SkeletonMage\\SkMageAtkRight.png");
		at->Create(L"SkMageAtkRight", SkMageAtkRightTex, Vector2(0.0f, 0.0f), Vector2(47.0f, 41.0f), 8, Vector2::Zero, 0.12f);

		//Idle
		std::shared_ptr<Texture> SkMageIdleTex
			= Resources::Load<Texture>(L"SkMageIdleTex", L"..\\Resources\\Texture\\Monster\\SkeletonMage\\SkMageIdle.png");
		at->Create(L"SkMageIdle", SkMageIdleTex, Vector2(0.0f, 0.0f), Vector2(25.0f, 40.0f), 6);
		

		at->PlayAnimation(L"SkMageIdle", true);


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
	SkeletonMage::~SkeletonMage()
	{
		mHpBar->SetState(eState::Dead);
		mHpBarFill->SetState(eState::Dead);
	}
	void SkeletonMage::Initialize()
	{
		GameObject::Initialize();
	}
	void SkeletonMage::Update()
	{
		GameObject::Update();

		mCurHp = mMScript->GetHP();
		if (mCurHp != mPrevHp)
		{
			mHpBarFill->ChangeHP(mCurHp);

			mPrevHp = mCurHp;
		}

	}
	void SkeletonMage::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void SkeletonMage::Render()
	{
		GameObject::Render();
	}
}
