#include "ssAnubis.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssInput.h"
#include "ssCollider2D.h"
#include "ssAnubisScript.h"
#include "ssBossHpBar.h"
#include "ssPlayerScript.h"
#include "ssImmuneText.h"

namespace ss
{
	Anubis::Anubis()
		: mCurHp(10000.0f)
		, mPrevHp(10000.0f)
	{
		SetName(L"Anubis");
		
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(1.5f, 1.5f, 1.0f);
		mPos = mTransform->GetPosition();

		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::NormalMonster);
		mCollider->SetSize(Vector2(0.4f, 0.6f));
		mCollider->SetCenter(Vector2(0.0f, -0.1f));

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		mAnimator = AddComponent<Animator>();
		std::shared_ptr<Texture> Anubis_DownTex
			= Resources::Load<Texture>(L"Anubis_DownTex", L"..\\Resources\\Texture\\Monster\\Anubis\\AnubisDown82_151_9.png");
		mAnimator->Create(L"Anubis_Down", Anubis_DownTex, Vector2(0.0f, 0.0f), Vector2(82, 151.0f), 9);

		std::shared_ptr<Texture> Anubis_CastTex
			= Resources::Load<Texture>(L"Anubis_CastTex", L"..\\Resources\\Texture\\Monster\\Anubis\\AnubisCast126_151.png");
		mAnimator->Create(L"Anubis_Cast", Anubis_CastTex, Vector2(0.0f, 0.0f), Vector2(126.0f, 151.0f), 30);

		std::shared_ptr<Texture> AnubisDeadEffectTex
			= Resources::Load<Texture>(L"AnubisDeadEffectTex", L"..\\Resources\\Texture\\Monster\\Anubis\\SoulExplosion305211.png");
		mAnimator->Create(L"AnubisDeadEffect", AnubisDeadEffectTex, Vector2(0.0f, 0.0f), Vector2(30.0f, 52.0f), 11);

		mScript = AddComponent<AnubisScript>();

		mText = new ImmuneText();
		mText->GetComponent<Transform>()->SetParent(mTransform);
		Vector3 tempPos2 = mText->GetComponent<Transform>()->GetPosition();
		mScript->SetImmuneText(mText);
		AddOtherGameObject(mText, eLayerType::MonsterUI);
	}

	Anubis::~Anubis()
	{
	}

	void Anubis::Initialize()
	{
		GameObject::Initialize();
	}
	void Anubis::Update()
	{
		GameObject::Update();

		mPos = mTransform->GetPosition();

		if (!mbAwake)
			Sleep();
	}
	void Anubis::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Anubis::Render()
	{
		GameObject::Render();
	}
	void Anubis::Sleep()
	{
		Vector3 PlayerPos = PlayerScript::GetPlayerPos();
		if (math::GetDistance(mPos, PlayerPos) < 1.8f)
		{
			mScript->Awake();
			mbAwake = true;
		}
	}
	void Anubis::SetBossHpFill(BossHpFill* fill)
	{
		mScript->SetBossHpFill(fill);
	}
	
}
