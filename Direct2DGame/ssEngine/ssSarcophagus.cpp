#include "ssSarcophagus.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssSkeletonScript.h"
#include "ssEnemyHpBar.h"
#include "ssEnemyHpBarFill.h"
#include "ssMummy.h"
#include "ssTime.h"
#include "ssSceneManager.h"
#include "ssAnubisScript.h"

namespace ss
{
	Sarcophagus::Sarcophagus()
		: mCurHp(1000.0f)
		, mPrevHp(1000.0f)
		, mSpawnTime(2.0f)
	{
		SetName(L"Sarcophagus");
		//mMScript = AddComponent<SkeletonScript>();
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(1.3f, 1.3f, 1.0f);

		//콜라이더 세팅
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::NormalMonster);
		collider->SetSize(Vector2(0.16f, 0.34f));
		collider->SetCenter(Vector2(-0.00f, 0.0f));

		//렌더
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		Animator* at = AddComponent<Animator>();

		//Move Ani
		std::shared_ptr<Texture> SarcoTex
			= Resources::Load<Texture>(L"SarcoTex", L"..\\Resources\\Texture\\Monster\\Mummy\\Sarkofagus_spr.png");
		at->Create(L"Sarco", SarcoTex, Vector2(0.0f, 0.0f), Vector2(35.0f, 77.0f), 1);
		at->PlayAnimation(L"Sarco", true);

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
	Sarcophagus::~Sarcophagus()
	{
		mHpBar->SetState(eState::Dead);
		mHpBarFill->SetState(eState::Dead);
	}
	void Sarcophagus::Initialize()
	{
		GameObject::Initialize();
	}
	void Sarcophagus::Update()
	{
		GameObject::Update();

		mPos = mTransform->GetPosition();

		DamageCheck();
		if (mCurHp != mPrevHp)
		{
			mHpBarFill->ChangeHP(mCurHp);

			mPrevHp = mCurHp;
		}

		SummonMummy();

	}
	void Sarcophagus::LateUpdate()
	{
		GameObject::LateUpdate();

		if (mCurHp <= 0)
		{
			SetState(eState::Dead);
			AnubisScript::SarcoDefeat();
		}
	}
	void Sarcophagus::Render()
	{
		GameObject::Render();
	}
	void Sarcophagus::DamageCheck()
	{
		float value = GetChangeHpValue();
		if (value != 0)
		{
			mCurHp += value;
			SetChangeHpValue(0.f);
		}
	}
	void Sarcophagus::SummonMummy()
	{
		mSpawnTime -= Time::DeltaTime();

		if (mSpawnTime <= 0.f)
		{
			mSpawnTime = 10.0f;
			Mummy* mum = new Mummy();
			switch (mDir)
			{
			case ss::Sarcophagus::eDir::LeftTop:
				mum->GetComponent<Transform>()->SetPosition(mPos.x + 0.3f, mPos.y - 0.3f, mPos.z);
				break;
			case ss::Sarcophagus::eDir::RightTop:
				mum->GetComponent<Transform>()->SetPosition(mPos.x - 0.3f, mPos.y - 0.3f, mPos.z);
				break;
			case ss::Sarcophagus::eDir::LeftBottom:
				mum->GetComponent<Transform>()->SetPosition(mPos.x + 0.3f, mPos.y + 0.3f, mPos.z);
				break;
			case ss::Sarcophagus::eDir::RightBottom:
				mum->GetComponent<Transform>()->SetPosition(mPos.x - 0.3f, mPos.y + 0.3f, mPos.z);
				break;
			default:
				break;
			}
			
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::Summon2, mum);
		}
	}
}
