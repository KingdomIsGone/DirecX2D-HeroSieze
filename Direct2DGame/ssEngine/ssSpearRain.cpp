#include "ssSpearRain.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"
#include "ssDamageScript.h"
#include "ssConstantBuffer.h"
#include "ssRenderer.h"
#include "ssSpearPiece.h"
#include "ssSceneManager.h"
#include "ssAudioClip.h"
#include "ssAudioSource.h"

namespace ss
{

	SpearRain::SpearRain()
		: mShadowScale(1.f)
		, mStage(0)
	{
		SetName(L"SpearRain");
		

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(mShadowScale, mShadowScale, 1.0f));

		
		mAnimator = AddComponent<Animator>();
		
		mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"AlphaAnimationMaterial"));

		std::shared_ptr<Texture> ShadowTex
			= Resources::Load<Texture>(L"ShadowTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Shadow.png");
		
		mAnimator->SetLarge(true);
		mAnimator->Create(L"Shadow", ShadowTex, Vector2(0.0f, 0.0f), Vector2(270.f, 180.0f), 1);
		
		GameObject* audioSpeaker = new GameObject();
		mAs = audioSpeaker->AddComponent<AudioSource>();
		mAs->SetClip(Resources::Load<AudioClip>(L"rain", L"..\\Resources\\Sound\\Valkyrie\\rain.wav"));
	}
	SpearRain::~SpearRain()
	{
	}
	void SpearRain::Initialize()
	{
		GameObject::Initialize();
	}
	void SpearRain::Update()
	{
		GameObject::Update();

		mPos = mTransform->GetPosition();

		if (mStage == 0)
		{
			MakeShadow();
		}
		else if (mStage == 1)
		{

			mAniComplete = true;
			mr->SetNoRender(true);
			mStage++;
			
		}
		else if (mStage == 2)
		{
			mDeadSign = true;
		}

	}

	void SpearRain::LateUpdate()
	{
		GameObject::LateUpdate();

		if (mDeadSign)
			SetState(eState::Dead);
	}
	void SpearRain::Render()
	{
		GameObject::Render();
	}
	void SpearRain::MakeShadow()
	{
		BindCB(0.5f);
		mAnimator->PlayAnimation(L"Shadow", true);

		mShadowScale += 4.5f * Time::DeltaTime();
		mTransform->SetScale(mShadowScale, mShadowScale, 1.f);
		
		if (mShadowScale > 10.f)
			mStage = 1;
	}
	
	void SpearRain::BindCB(float alpha)
	{
		ss::graphics::ConstantBuffer* cb
			= renderer::constantBuffer[(int)eCBType::BossEffect2];

		renderer::BossEffectCB2 data;
		
		data.A = 0.5f;
		
		data.TransAlpha = alpha;

		cb->SetData(&data);

		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::VS);

	}
}
