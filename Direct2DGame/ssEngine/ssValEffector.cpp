#include "ssValEffector.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssValkyrieScript.h"
#include "ssRenderer.h"
#include "ssValkyrie.h"

namespace ss
{
	ValEffector::ValEffector()
		: mOffset(Vector3::Zero)
		, mDeathStage(0)
		, mChargeStage(0)
	{
		SetName(L"ValEffector");

		mTransform = GetComponent<Transform>();


		mAnimator = AddComponent<Animator>();
		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"BossEffectMaterial"));


		//ani setting
		{
			//lightning
			std::shared_ptr<Texture> LightningEffectTex
				= Resources::Load<Texture>(L"LightningEffectTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\LightningImpact.png");
			mAnimator->Create(L"LightningEffect", LightningEffectTex, Vector2(0.0f, 0.0f), Vector2(70.f, 70.f), 8, Vector2::Zero, 0.05f);
			
			std::shared_ptr<Texture> LightningBlankTex
				= Resources::Load<Texture>(L"LightningBlankTex", L"..\\Resources\\Texture\\Blank.png");
			mAnimator->Create(L"LightningBlank", LightningBlankTex, Vector2(0.0f, 0.0f), Vector2(1.f, 1.f), 1);

			std::shared_ptr<Texture> ValDeathEffectTex
				= Resources::Load<Texture>(L"ValDeathEffectTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\ValDeathEffect.png");
			mAnimator->Create(L"ValDeathEffect", ValDeathEffectTex, Vector2(0.0f, 0.0f), Vector2(50.f, 56.f), 25, Vector2::Zero, 0.1f);

			mAnimator->SetLarge(true);

			std::shared_ptr<Texture> ValChargeNewTex
				= Resources::Load<Texture>(L"ValChargeNewTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\Charge\\ChargeNew.png");
			mAnimator->Create(L"ValChargeNew", ValChargeNewTex, Vector2(0.0f, 0.0f), Vector2(136.f, 236.f), 7, Vector2::Zero, 0.1f);

			std::shared_ptr<Texture> ValChargeMiddleTex
				= Resources::Load<Texture>(L"ValChargeMiddleTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\Charge\\ChargeMiddle.png");
			mAnimator->Create(L"ValChargeMiddle", ValChargeMiddleTex, Vector2(0.0f, 0.0f), Vector2(136.f, 236.f), 6, Vector2::Zero, 0.1f);

			std::shared_ptr<Texture> ValChargeEndTex
				= Resources::Load<Texture>(L"ValChargeEndTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\Charge\\ChargeEnd.png");
			mAnimator->Create(L"ValChargeEnd", ValChargeEndTex, Vector2(0.0f, 0.0f), Vector2(136.f, 236.f), 8, Vector2::Zero, 0.1f);

			std::shared_ptr<Texture> ValDeathEffect2Tex
				= Resources::Load<Texture>(L"ValDeathEffect2Tex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\ValDeathEffect2.png");
			mAnimator->Create(L"ValDeathEffect2", ValDeathEffect2Tex, Vector2(0.0f, 0.0f), Vector2(320.f, 320.f), 19, Vector2::Zero, 0.1f);
			
		}

		
	}

	ValEffector::~ValEffector()
	{
	}
	void ValEffector::Initialize()
	{
		GameObject::Initialize();
	}
	void ValEffector::Update()
	{
		GameObject::Update();

		mValkPos = mValk->GetComponent<Transform>()->GetPosition();
		mValkPos.z -= 0.01f;
		mValkPos += mOffset;
		mTransform->SetPosition(mValkPos);

		if (mAnimator->GetActiveAnimation() != nullptr
			&& mAnimator->GetActiveAnimation()->IsComplete()
			&& mAnimator->GetActiveAnimation()->GetKey() == L"LightningEffect")
			mAnimator->PlayAnimation(L"LightningBlank", true);
	}
	void ValEffector::LateUpdate()
	{
		GameObject::LateUpdate();

		
	}
	void ValEffector::Render()
	{
		GameObject::Render();
	}

	void ValEffector::BindCB(float Radd, float Gadd, float Badd, float A)
	{
		ss::graphics::ConstantBuffer* cb
			= renderer::constantBuffer[(int)eCBType::BossEffect];

		renderer::BossEffectCB data;

		data.Radd = Radd;
		data.Gadd = Gadd;
		data.Badd = Badd;
		data.A = A;

		cb->SetData(&data);

		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::VS);

	}

	void ValEffector::PlayNormalRushEffect(e4Direction dir)
	{
		BindCB(0.4f, 0.4f, 0.f, .9f);
		mTransform->SetScale(1.f, 1.f, 1.f);

		switch (dir)
		{
		case ss::enums::e4Direction::Up:
			mOffset = Vector3(0.08f, 0.29f, 0.0f); //up
			break;
		case ss::enums::e4Direction::Down:
			mOffset = Vector3(-0.03f, -0.3f, 0.0f); //down
			break;
		case ss::enums::e4Direction::Right:
			mOffset = Vector3(0.4f, -0.04f, 0.0f); //right
			break;
		case ss::enums::e4Direction::Left:
			mOffset = Vector3(-0.33f, -0.037f, 0.0f); //left
			break;
		default:
			break;
		}
		
		mAnimator->PlayAnimation(L"LightningEffect", false);
	}

	void ValEffector::PlayDeathEffect()
	{
		if (mDeathStage == 0)
		{
			mTransform->SetScale(4.f, 4.f, 1.f);

			BindCB(0.0f, 0.f, 0.3f, 0.7f);

			mOffset = Vector3(-0.012f, 0.24f, 0.0f);
			mAnimator->SetLarge(false);
			mAnimator->PlayAnimation(L"ValDeathEffect", false);

			if (mAnimator->GetActiveAnimation()->IsComplete())
				mDeathStage++;
		}
		else if (mDeathStage == 1)
		{
			mTransform->SetScale(20.f, 20.f, 1.f);

			BindCB(-0.7f, 0.f, 0.6f, 0.75f);

			mOffset = Vector3(-0.02f, 0.15f, 0.0f);
			
			mAnimator->PlayAnimation(L"ValDeathEffect2", false);

			mDeathAniPlayed = true;
			if (mAnimator->GetActiveAnimation()->IsComplete())
				mDeathStage++;
		}
		else if (mDeathStage == 2)
		{
			
		}


	}

	void ValEffector::PlayChargeEffectNew()
	{
		mTransform->SetScale(10.f, 10.f, 1.f);

		BindCB(0.f, 0.f, 0.0f, 0.75f);

		mOffset = Vector3(0.03f, 0.1f, 0.0f);
		mAnimator->PlayAnimation(L"ValChargeNew", false);
	}

	void ValEffector::PlayChargeEffectMiddle()
	{
		mTransform->SetScale(10.f, 10.f, 1.f);

		BindCB(0.f, 0.f, 0.0f, 0.75f);

		mOffset = Vector3(0.03f, 0.1f, 0.0f);
		mAnimator->PlayAnimation(L"ValChargeMiddle", true);
	}

	bool ValEffector::PlayChargeNewAndMiddle()
	{
		if (mChargeStage == 0)
		{
			PlayChargeEffectNew();
			if (mAnimator->GetActiveAnimation()->IsComplete())
				mChargeStage++;
		}
		else if (mChargeStage == 1)
		{
			PlayChargeEffectMiddle();
			return true;
		}
		
		return false;
	}

	bool ValEffector::PlayChargeEffectEnd()
	{
		mChargeStage = 0;
		mTransform->SetScale(10.f, 10.f, 1.f);

		BindCB(0.f, 0.f, 0.0f, 0.75f);

		mOffset = Vector3(0.03f, 0.1f, 0.0f);
		mAnimator->PlayAnimation(L"ValChargeEnd", false);

		if (mAnimator->GetActiveAnimation()->IsComplete())
		{
			return true;
		}

		return false;
	}

	
	

}


