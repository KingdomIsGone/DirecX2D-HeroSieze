#include "ssMummy.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssSkeletonScript.h"
#include "ssEnemyHpBar.h"
#include "ssEnemyHpBarFill.h"
#include "ssMummyScript.h"

namespace ss
{
	Mummy::Mummy()
		: mCurHp(500.0f)
		, mPrevHp(500.0f)
	{
		SetName(L"Mummy");
		mScript = AddComponent<MummyScript>();

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

		//Attack Ani
		std::shared_ptr<Texture> Mummy_UpAtkTex
			= Resources::Load<Texture>(L"Mummy_UpAtkTex", L"..\\Resources\\Texture\\Monster\\Mummy\\MummyUpAtk194313.png");
		at->Create(L"MummyUpAtk", Mummy_UpAtkTex, Vector2(0.0f, 0.0f), Vector2(19.0f, 43.0f), 13);

		std::shared_ptr<Texture> Mummy_DownAtkTex
			= Resources::Load<Texture>(L"Mummy_DownAtkTex", L"..\\Resources\\Texture\\Monster\\Mummy\\MummyDownAtk204613.png");
		at->Create(L"MummyDownAtk", Mummy_DownAtkTex, Vector2(0.0f, 0.0f), Vector2(20.0f, 46.0f), 13);
		
		std::shared_ptr<Texture> Mummy_RightATKTex
			= Resources::Load<Texture>(L"Mummy_RightATKTex", L"..\\Resources\\Texture\\Monster\\Mummy\\MummyRIghtAtk403914.png");
		at->Create(L"MummyRightAtk", Mummy_RightATKTex, Vector2(0.0f, 0.0f), Vector2(40.0f, 39.0f), 14);

		std::shared_ptr<Texture> Mummy_LeftAtkTex
			= Resources::Load<Texture>(L"Mummy_LeftAtkTex", L"..\\Resources\\Texture\\Monster\\Mummy\\MummyLeftAtk403914.png");
		at->Create(L"MummyLeftAtk", Mummy_LeftAtkTex, Vector2(0.0f, 0.0f), Vector2(40.0f, 39.0f), 14);

		//Move Ani
		std::shared_ptr<Texture> Mummy_UpTex
			= Resources::Load<Texture>(L"Mummy_UpTex", L"..\\Resources\\Texture\\Monster\\Mummy\\MummyUp19438.png");
		at->Create(L"MummyUp", Mummy_UpTex, Vector2(0.0f, 0.0f), Vector2(19.0f, 43.0f), 8);

		std::shared_ptr<Texture> Mummy_DownTex
			= Resources::Load<Texture>(L"Mummy_DownTex", L"..\\Resources\\Texture\\Monster\\Mummy\\MummyDown21438.png");
		at->Create(L"MummyDown", Mummy_DownTex, Vector2(0.0f, 0.0f), Vector2(21.0f, 43.0f), 8);

		std::shared_ptr<Texture> Mummy_RightTex
			= Resources::Load<Texture>(L"Mummy_RightTex", L"..\\Resources\\Texture\\Monster\\Mummy\\MummyRight24418.png");
		at->Create(L"MummyRight", Mummy_RightTex, Vector2(0.0f, 0.0f), Vector2(24.0f, 41.0f), 8);

		std::shared_ptr<Texture> Mummy_LeftTex
			= Resources::Load<Texture>(L"Mummy_LeftTex", L"..\\Resources\\Texture\\Monster\\Mummy\\MummyLeft24418.png");
		at->Create(L"MummyLeft", Mummy_LeftTex, Vector2(0.0f, 0.0f), Vector2(24.0f, 41.0f), 8);

		at->PlayAnimation(L"MummyDown", true);

		//hp바, fill
		mHpBar = new EnemyHpBar();
		mTransform = GetComponent<Transform>();
		mHpBar->GetComponent<Transform>()->SetParent(mTransform);
		AddOtherGameObject(mHpBar, eLayerType::MonsterUI);

		mHpBarFill = new EnemyHpBarFill();
		mHpBarFill->GetComponent<Transform>()->SetParent(mTransform);
		Vector3 tempPos2 = mHpBarFill->GetComponent<Transform>()->GetPosition();
		AddOtherGameObject(mHpBarFill, eLayerType::MonsterUI);
	}

	Mummy::~Mummy()
	{
		mHpBar->SetState(eState::Dead);
		mHpBarFill->SetState(eState::Dead);
	}
	void Mummy::Initialize()
	{
		GameObject::Initialize();
	}
	void Mummy::Update()
	{
		GameObject::Update();

		mCurHp = mScript->GetHP();
		if (mCurHp != mPrevHp)
		{
			mHpBarFill->ChangeHP(mCurHp);

			mPrevHp = mCurHp;
		}
	}
	void Mummy::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Mummy::Render()
	{
		GameObject::Render();
	}
}

