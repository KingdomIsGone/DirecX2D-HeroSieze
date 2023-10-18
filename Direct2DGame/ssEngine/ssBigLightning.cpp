#include "ssBigLightning.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssValkyrieScript.h"
#include "ssRenderer.h"
#include "ssValkyrie.h"
#include "ssBigLightningScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"

namespace ss
{
	BigLightning::BigLightning()
		: mOffset(Vector3::Zero)
		, mStage(0)
		, mRotation(0.f)
	{
		SetName(L"ValEffector");

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(20.f, 20.f, 1.f);
		mPos = mTransform->GetPosition();

		mCollider = AddComponent<Collider2D>();
		mCollider->SetSize(Vector2(0.1f, 0.1f));

		mAnimator = AddComponent<Animator>();
		mAnimator->SetLarge(true);
		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"BossEffectMaterial2"));


		//ani setting
		{
			std::shared_ptr<Texture> BigLightningTex
				= Resources::Load<Texture>(L"BigLightningTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\BigLightningBefore.png");
			mAnimator->Create(L"BigLightningBefore", BigLightningTex, Vector2(0.0f, 0.0f), Vector2(178.f, 457.f), 8, Vector2::Zero, 0.08f);
			
			std::shared_ptr<Texture> BigLightningAfterTex
				= Resources::Load<Texture>(L"BigLightningAfterTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\BigLightningAfter.png");
			mAnimator->Create(L"BigLightningAfter", BigLightningAfterTex, Vector2(0.0f, 0.0f), Vector2(256.f, 256.f), 14, Vector2::Zero, 0.08f);
			
			std::shared_ptr<Texture> SpellCircleTex
				= Resources::Load<Texture>(L"SpellCircleTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\SpellPoint.png");
			mAnimator->Create(L"SpellCircle", SpellCircleTex, Vector2(0.0f, 0.0f), Vector2(213.f, 213.f), 1, Vector2::Zero, 0.08f);
		
		}

		mScript = AddComponent<BigLightningScript>();

	}

	BigLightning::~BigLightning()
	{
	}
	void BigLightning::Initialize()
	{
		GameObject::Initialize();
	}
	void BigLightning::Update()
	{
		GameObject::Update();

		if (mStage == 0)
		{
			Vector3 playerPos = PlayerScript::GetPlayerPos();

			if (playerPos.x < mPos.x)
				mPos.x -= 0.5f * Time::DeltaTime();
			else
				mPos.x += 0.5f * Time::DeltaTime();

			if (playerPos.y < mPos.y)
				mPos.y -= 0.5f * Time::DeltaTime();
			else
				mPos.y += 0.5f * Time::DeltaTime();
		}

		PlayAni();
	}
	void BigLightning::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void BigLightning::Render()
	{
		GameObject::Render();
	}

	void BigLightning::BindCB(float Radd, float Gadd, float Badd, float A)
	{
		ss::graphics::ConstantBuffer* cb
			= renderer::constantBuffer[(int)eCBType::BossEffect2];

		renderer::BossEffectCB2 data;

		data.Radd = Radd;
		data.Gadd = Gadd;
		data.Badd = Badd;
		data.A = A;
		data.DiscardLight = 0.22;

		cb->SetData(&data);

		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::VS);
	}

	void BigLightning::PlayAni()
	{
		if (mStage == 0)
		{
			Vector3 startPos = mPos;
			startPos.z += 0.1f;
			mTransform->SetPosition(startPos);
			BindCB(0.f, 0.f, 0.0f, 0.5f);
			mAnimator->PlayAnimation(L"SpellCircle", true);

			mRotation += 1.f * Time::DeltaTime();

			mTransform->SetRotation(0.0f, 0.f, mRotation);

			if (mRotation > 3.f)
			{
				mStage = 1;
				mRotation = 0.f;
			}
		}
		else if (mStage == 1)
		{
			mTransform->SetRotation(0.0f, 0.f, 0.f);
			BindCB(0.f, 0.f, 0.0f, 0.9f);
			Vector3 beforePos = mPos;
			beforePos.x += -0.12f;
			beforePos.y += 1.55f;
			beforePos.z -= 0.1f;
			mTransform->SetPosition(beforePos);

			mAnimator->PlayAnimation(L"BigLightningBefore", false);

			if (mAnimator->GetActiveAnimation()->IsComplete())
				mStage = 2;
		}
		else if (mStage == 2)
		{
			mTransform->SetPosition(mPos);
			mScript->SetDamageApply(true);

			mAnimator->PlayAnimation(L"BigLightningAfter", false);

			if (mAnimator->GetActiveAnimation()->IsComplete())
				mStage = 3;
		}
		else if (mStage == 3)
		{
			SetState(eState::Dead);
		}

	}



}


