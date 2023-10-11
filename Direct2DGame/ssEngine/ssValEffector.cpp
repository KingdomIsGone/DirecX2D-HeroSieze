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
			std::shared_ptr<Texture> LightningEffectTex
				= Resources::Load<Texture>(L"LightningEffectTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\LightningImpact.png");
			mAnimator->Create(L"LightningEffect", LightningEffectTex, Vector2(0.0f, 0.0f), Vector2(70.f, 70.f), 8);
			
			std::shared_ptr<Texture> LightningBlankTex
				= Resources::Load<Texture>(L"LightningBlankTex", L"..\\Resources\\Texture\\Blank.png");
			mAnimator->Create(L"LightningBlank", LightningBlankTex, Vector2(0.0f, 0.0f), Vector2(1.f, 1.f), 1);
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
			&& mAnimator->GetActiveAnimation()->IsComplete())
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

}


