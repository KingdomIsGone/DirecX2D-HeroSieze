#include "ssBear.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssEnemyHpBar.h"
#include "ssEnemyHpBarFill.h"
#include "ssBearScript.h"

namespace ss
{
	Bear::Bear()
		: mCurHp(2200.0f)
		, mPrevHp(2200.0f)
	{
		SetName(L"Bear");
		

		//콜라이더 세팅
		GetComponent<Transform>()->SetScale(16.f, 18.f, 1.0f);
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::NormalMonster);
		collider->SetSize(Vector2(0.05f, 0.05f));
		collider->SetCenter(Vector2(-0.00f, 0.0f));

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		Animator* at = AddComponent<Animator>();
		at->SetLarge(true);

		//ani
		{
			//Attack Ani
			std::shared_ptr<Texture> Bear_UpAtkTex
				= Resources::Load<Texture>(L"Bear_UpAtkTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearAtk\\BearAtkUp.png");
			at->Create(L"Bear_UpAtk", Bear_UpAtkTex, Vector2(0.0f, 0.0f), Vector2(143.0f, 117.0f), 8, Vector2(0.007f, 0.f));

			std::shared_ptr<Texture> Bear_DownAtkTex
				= Resources::Load<Texture>(L"Bear_DownAtkTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearAtk\\BearAtkDown.png");
			at->Create(L"Bear_DownAtk", Bear_DownAtkTex, Vector2(0.0f, 0.0f), Vector2(135.0f, 143.0f), 8);

			std::shared_ptr<Texture> Bear_RightAtkTex
				= Resources::Load<Texture>(L"Bear_RightAtkTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearAtk\\BearAtkRight.png");
			at->Create(L"Bear_RightAtk", Bear_RightAtkTex, Vector2(0.0f, 0.0f), Vector2(136.0f, 145.0f), 8, Vector2(0.f, -0.14f));

			std::shared_ptr<Texture> Bear_LeftAtkTex
				= Resources::Load<Texture>(L"Bear_LeftAtkTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearAtk\\BearAtkLeft.png");
			at->Create(L"Bear_LeftAtk", Bear_LeftAtkTex, Vector2(0.0f, 0.0f), Vector2(136.0f, 145.0f), 8, Vector2(0.f, -0.14f));

			//Attack2 Ani
			std::shared_ptr<Texture> Bear_UpAtk2Tex
				= Resources::Load<Texture>(L"Bear_UpAtk2Tex", L"..\\Resources\\Texture\\Monster\\Bear\\BearAtk2\\BearAtkUp2.png");
			at->Create(L"Bear_UpAtk2", Bear_UpAtk2Tex, Vector2(0.0f, 0.0f), Vector2(166.0f, 131.0f), 12, Vector2(0.01f, 0.f));

			std::shared_ptr<Texture> Bear_DownAtk2Tex
				= Resources::Load<Texture>(L"Bear_DownAtk2Tex", L"..\\Resources\\Texture\\Monster\\Bear\\BearAtk2\\BearAtkDown2.png");
			at->Create(L"Bear_DownAtk2", Bear_DownAtk2Tex, Vector2(0.0f, 0.0f), Vector2(157.0f, 215.0f), 12, Vector2(-0.006f, -0.14f));

			std::shared_ptr<Texture> Bear_RightAtk2Tex
				= Resources::Load<Texture>(L"Bear_RightAtk2Tex", L"..\\Resources\\Texture\\Monster\\Bear\\BearAtk2\\BearAtkRight2.png");
			at->Create(L"Bear_RightAtk2", Bear_RightAtk2Tex, Vector2(0.0f, 0.0f), Vector2(144.0f, 221.0f), 12, Vector2(0.002f, -0.27f));

			std::shared_ptr<Texture> Bear_LeftAtk2Tex
				= Resources::Load<Texture>(L"Bear_LeftAtk2Tex", L"..\\Resources\\Texture\\Monster\\Bear\\BearAtk2\\BearAtkLeft2.png");
			at->Create(L"Bear_LeftAtk2", Bear_LeftAtk2Tex, Vector2(0.0f, 0.0f), Vector2(144.0f, 221.0f), 12, Vector2(-0.002f, -0.27f));

			//Move Ani
			std::shared_ptr<Texture> Bear_UpTex
				= Resources::Load<Texture>(L"Bear_UpTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearWalk\\BearWalkUp.png");
			at->Create(L"Bear_Up", Bear_UpTex, Vector2(0.0f, 0.0f), Vector2(98.0f, 114.0f), 12);

			std::shared_ptr<Texture> Bear_DownTex
				= Resources::Load<Texture>(L"Bear_DownTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearWalk\\BearWalkDown.png");
			at->Create(L"Bear_Down", Bear_DownTex, Vector2(0.0f, 0.0f), Vector2(98.0f, 119.0f), 12);

			std::shared_ptr<Texture> Bear_RightTex
				= Resources::Load<Texture>(L"Bear_RightTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearWalk\\BearWalkRight.png");
			at->Create(L"Bear_Right", Bear_RightTex, Vector2(0.0f, 0.0f), Vector2(90.0f, 109.0f), 12);

			std::shared_ptr<Texture> Bear_LeftTex
				= Resources::Load<Texture>(L"Bear_LeftTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearWalk\\BearWalkLeft.png");
			at->Create(L"Bear_Left", Bear_LeftTex, Vector2(0.0f, 0.0f), Vector2(90.0f, 109.0f), 12);

			//dieAni
			std::shared_ptr<Texture> Bear_DieLeftTex
				= Resources::Load<Texture>(L"Bear_DieLeftTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearDie\\BearDieLeft.png");
			at->Create(L"Bear_DieLeft", Bear_DieLeftTex, Vector2(0.0f, 0.0f), Vector2(121.0f, 111.0f), 14);

			std::shared_ptr<Texture> Bear_DieRightTex
				= Resources::Load<Texture>(L"Bear_DieRightTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearDie\\BearDieRight.png");
			at->Create(L"Bear_DieRight", Bear_DieRightTex, Vector2(0.0f, 0.0f), Vector2(121.0f, 111.0f), 14);

			std::shared_ptr<Texture> Bear_DieDownTex
				= Resources::Load<Texture>(L"Bear_DieDownTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearDie\\BearDieDown.png");
			at->Create(L"Bear_DieDown", Bear_DieDownTex, Vector2(0.0f, 0.0f), Vector2(98.0f, 165.0f), 14);

			std::shared_ptr<Texture> Bear_DieUpTex
				= Resources::Load<Texture>(L"Bear_DieUpTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearDie\\BearDieUp.png");
			at->Create(L"Bear_DieUp", Bear_DieUpTex, Vector2(0.0f, 0.0f), Vector2(98.0f, 114.0f), 14);

			//IdleAni
			std::shared_ptr<Texture> Bear_IdleTex
				= Resources::Load<Texture>(L"Bear_IdleTex", L"..\\Resources\\Texture\\Monster\\Bear\\BearIdleDown.png");
			at->Create(L"Bear_Idle", Bear_IdleTex, Vector2(0.0f, 0.0f), Vector2(98.0f, 110.0f), 7);
		}
		at->PlayAnimation(L"Bear_Idle", true);

		//hp바, fill
		mHpBar = new EnemyHpBar();
		mTransform = GetComponent<Transform>();
		mHpBar->SetOwnerTransform(mTransform);
		mHpBar->SetOffset(0.f, 0.6f);
		mHpBar->GetComponent<Transform>()->SetScale(Vector3(1.4f, 0.1f, 1.f));
		AddOtherGameObject(mHpBar, eLayerType::MonsterUI);

		mHpBarFill = new EnemyHpBarFill();
		mHpBarFill->SetOwnerTransform(mTransform);
		mHpBarFill->SetOffset(0.0f, 0.61f);
		mHpBarFill->SetFullHp(mCurHp);
		mHpBarFill->SetFullScale(0.5f, 0.02f);
		AddOtherGameObject(mHpBarFill, eLayerType::MonsterUI);

		mScript = AddComponent<BearScript>();
	}

	Bear::~Bear()
	{
		mHpBar->SetState(eState::Dead);
		mHpBarFill->SetState(eState::Dead);
	}
	void Bear::Initialize()
	{
		GameObject::Initialize();
	}
	void Bear::Update()
	{
		GameObject::Update();

		mCurHp = mScript->GetHP();
		if (mCurHp != mPrevHp)
		{
			mHpBarFill->ChangeHP(mCurHp);

			mPrevHp = mCurHp;
		}
	}
	void Bear::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Bear::Render()
	{
		GameObject::Render();
	}
	void Bear::SetItmeHave(UINT num)
	{
		mScript->SetItemHave(num);
	}
}

