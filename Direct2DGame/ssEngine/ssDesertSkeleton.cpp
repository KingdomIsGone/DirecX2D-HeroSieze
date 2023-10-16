#include "ssDesertSkeleton.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssSkeletonScript.h"
#include "ssEnemyHpBar.h"
#include "ssEnemyHpBarFill.h"

namespace ss
{
	DesertSkeleton::DesertSkeleton()
		: mCurHp(1000.0f)
		, mPrevHp(1000.0f)
	{
		SetName(L"Skeleton");
		mMScript = AddComponent<SkeletonScript>();

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
		std::shared_ptr<Texture> Skeleton_UpTex
			= Resources::Load<Texture>(L"Skeleton_UpTex", L"..\\Resources\\Texture\\Monster\\Desert_Skeleton\\Move\\Desert_Skeleton_Up_spr36478.png");
		at->Create(L"SkeletonUp", Skeleton_UpTex, Vector2(0.0f, 0.0f), Vector2(36.0f, 47.0f), 8);
		
		std::shared_ptr<Texture> Skeleton_DownTex
			= Resources::Load<Texture>(L"Skeleton_DownTex", L"..\\Resources\\Texture\\Monster\\Desert_Skeleton\\Move\\Desert_Skeleton_Down_spr35487.png");
		at->Create(L"SkeletonDown", Skeleton_DownTex, Vector2(0.0f, 0.0f), Vector2(35.0f, 48.0f), 7);

		std::shared_ptr<Texture> Skeleton_LeftTex
			= Resources::Load<Texture>(L"Skeleton_LeftTex", L"..\\Resources\\Texture\\Monster\\Desert_Skeleton\\Move\\Desert_Skeleton_Left_spr41458.png");
		at->Create(L"SkeletonLeft", Skeleton_LeftTex, Vector2(0.0f, 0.0f), Vector2(41.0f, 45.0f), 8);

		std::shared_ptr<Texture> Skeleton_RightTex
			= Resources::Load<Texture>(L"Skeleton_RightTex", L"..\\Resources\\Texture\\Monster\\Desert_Skeleton\\Move\\Desert_Skeleton_Right_spr41458.png");
		at->Create(L"SkeletonRight", Skeleton_RightTex, Vector2(0.0f, 0.0f), Vector2(41.0f, 45.0f), 8);

		//Attack Ani
		std::shared_ptr<Texture> Skeleton_UpAtkTex
			= Resources::Load<Texture>(L"Skeleton_UpAtkTex", L"..\\Resources\\Texture\\Monster\\Desert_Skeleton\\Attack\\Desert_Skeleton_Up_Attack_spr385410.png");
		at->Create(L"Skeleton_UpAtk", Skeleton_UpAtkTex, Vector2(0.0f, 0.0f), Vector2(38.0f, 54.0f), 10);

		std::shared_ptr<Texture> Skeleton_DownAtkTex
			= Resources::Load<Texture>(L"Skeleton_DownAtkTex", L"..\\Resources\\Texture\\Monster\\Desert_Skeleton\\Attack\\Desert_Skeleton_Down_Attack_spr367510.png");
		at->Create(L"Skeleton_DownAtk", Skeleton_DownAtkTex, Vector2(0.0f, 0.0f), Vector2(36.0f, 75.0f), 10);

		std::shared_ptr<Texture> Skeleton_RightAtkTex
			= Resources::Load<Texture>(L"Skeleton_RightAtkTex", L"..\\Resources\\Texture\\Monster\\Desert_Skeleton\\Attack\\Desert_Skeleton_Right_Attack_spr614810.png");
		at->Create(L"Skeleton_RightAtk", Skeleton_RightAtkTex, Vector2(0.0f, 0.0f), Vector2(61.0f, 48.0f), 10);

		std::shared_ptr<Texture> Skeleton_LeftAtkTex
			= Resources::Load<Texture>(L"Skeleton_LeftAtkTex", L"..\\Resources\\Texture\\Monster\\Desert_Skeleton\\Attack\\Desert_Skeleton_Left_Attack_spr614810.png");
		at->Create(L"Skeleton_LeftAtk", Skeleton_LeftAtkTex, Vector2(0.0f, 0.0f), Vector2(61.0f, 48.0f), 10);



		
		at->PlayAnimation(L"SkeletonDown", true);
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
	DesertSkeleton::~DesertSkeleton()
	{
		mHpBar->SetState(eState::Dead);
		mHpBarFill->SetState(eState::Dead);
	}
	void DesertSkeleton::Initialize()
	{                              
		GameObject::Initialize();
	}
	void DesertSkeleton::Update()
	{
		GameObject::Update();

		mCurHp = mMScript->GetHP();
		if (mCurHp != mPrevHp)
		{
			mHpBarFill->ChangeHP(mCurHp);

			mPrevHp = mCurHp;
		}
		
	}
	void DesertSkeleton::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DesertSkeleton::Render()
	{
		GameObject::Render();
	}
}
