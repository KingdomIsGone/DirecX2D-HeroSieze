#include "ssTreeMon.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssEnemyHpBar.h"
#include "ssEnemyHpBarFill.h"
#include "ssTreeMonScript.h"

namespace ss
{
	TreeMon::TreeMon()
		: mCurHp(1000.0f)
		, mPrevHp(1000.0f)
	{
		SetName(L"TreeMon");
		mMScript = AddComponent<TreeMonScript>();

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
		std::shared_ptr<Texture> TreeMonWalkUpTex
			= Resources::Load<Texture>(L"TreeMonWalkUpTex", L"..\\Resources\\Texture\\Monster\\TreeMon\\TreeWalkUp.png");
		at->Create(L"TreeMonWalkUp", TreeMonWalkUpTex, Vector2(0.0f, 0.0f), Vector2(33.0f, 41.0f), 6);

		std::shared_ptr<Texture> TreeMonWalkDownTex
			= Resources::Load<Texture>(L"TreeMonWalkDownTex", L"..\\Resources\\Texture\\Monster\\TreeMon\\TreeWalkDown.png");
		at->Create(L"TreeMonWalkDown", TreeMonWalkDownTex, Vector2(0.0f, 0.0f), Vector2(37.0f, 50.0f), 6);

		std::shared_ptr<Texture> TreeMonWalkLeftTex
			= Resources::Load<Texture>(L"TreeMonWalkLeftTex", L"..\\Resources\\Texture\\Monster\\TreeMon\\TreeWalkLeft.png");
		at->Create(L"TreeMonWalkLeft", TreeMonWalkLeftTex, Vector2(0.0f, 0.0f), Vector2(36.0f, 48.0f), 6);

		std::shared_ptr<Texture> TreeMonWalkRightTex
			= Resources::Load<Texture>(L"TreeMonWalkRightTex", L"..\\Resources\\Texture\\Monster\\TreeMon\\TreeWalkRight.png");
		at->Create(L"TreeMonWalkRight", TreeMonWalkRightTex, Vector2(0.0f, 0.0f), Vector2(36.0f, 48.0f), 6);

		//Attack Ani
		std::shared_ptr<Texture> TreeMonAtkUpTex
			= Resources::Load<Texture>(L"TreeMonAtkUpTex", L"..\\Resources\\Texture\\Monster\\TreeMon\\TreeAtkUp.png");
		at->Create(L"TreeMonAtkUp", TreeMonAtkUpTex, Vector2(0.0f, 0.0f), Vector2(32.0f, 46.0f), 6, Vector2::Zero, 0.12f);
		std::shared_ptr<Texture> TreeMonAtkDownTex
			= Resources::Load<Texture>(L"TreeMonAtkDownTex", L"..\\Resources\\Texture\\Monster\\TreeMon\\TreeAtkDown.png");
		at->Create(L"TreeMonAtkDown", TreeMonAtkDownTex, Vector2(0.0f, 0.0f), Vector2(35.0f, 61.0f), 6, Vector2::Zero, 0.12f);
		std::shared_ptr<Texture> TreeMonAtkRightTex
			= Resources::Load<Texture>(L"TreeMonAtkRightTex", L"..\\Resources\\Texture\\Monster\\TreeMon\\TreeAtkRight.png");
		at->Create(L"TreeMonAtkRight", TreeMonAtkRightTex, Vector2(0.0f, 0.0f), Vector2(58.0f, 48.0f), 6, Vector2::Zero, 0.12f);

		std::shared_ptr<Texture> TreeMonAtkLeftTex
			= Resources::Load<Texture>(L"TreeMonAtkLeftTex", L"..\\Resources\\Texture\\Monster\\TreeMon\\TreeAtkLeft.png");
		at->Create(L"TreeMonAtkLeft", TreeMonAtkLeftTex, Vector2(0.0f, 0.0f), Vector2(58.0f, 48.0f), 6, Vector2::Zero, 0.12f);

		//Idle
		std::shared_ptr<Texture> TreeMonIdleTex
			= Resources::Load<Texture>(L"TreeMonIdleTex", L"..\\Resources\\Texture\\Monster\\TreeMon\\TreeIdle.png");
		at->Create(L"TreeMonIdle", TreeMonIdleTex, Vector2(0.0f, 0.0f), Vector2(37.0f, 50.0f), 4);

		at->PlayAnimation(L"TreeMonIdle", true);


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
	TreeMon::~TreeMon()
	{
		mHpBar->SetState(eState::Dead);
		mHpBarFill->SetState(eState::Dead);
	}
	void TreeMon::Initialize()
	{
		GameObject::Initialize();
	}
	void TreeMon::Update()
	{
		GameObject::Update();

		mCurHp = mMScript->GetHP();
		if (mCurHp != mPrevHp)
		{
			mHpBarFill->ChangeHP(mCurHp);

			mPrevHp = mCurHp;
		}

	}
	void TreeMon::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void TreeMon::Render()
	{
		GameObject::Render();
	}
}
