#include "ssValEffector.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssValkyrieScript.h"
#include "ssRenderer.h"

namespace ss
{
	ValEffector::ValEffector()
	{
		SetName(L"ValEffector");

		//콜라이더 세팅
		GetComponent<Transform>()->SetScale(1.3f, 1.3f, 1.0f);
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::NormalMonster);
		collider->SetSize(Vector2(0.15f, 0.24f));
		collider->SetCenter(Vector2(-0.00f, 0.0f));

		mAnimator = AddComponent<Animator>();
		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"BossEffectMaterial"));


		//ani setting
		/*{
			std::shared_ptr<Texture> LightningEffectTex
				= Resources::Load<Texture>(L"LightningEffectTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\LightningImpact.png");
			mAnimator->Create(L"LightningEffect", LightningEffectTex, Vector2(0.0f, 0.0f), Vector2(70.f, 70.f), 8);

		}

		mAnimator->PlayAnimation(L"LightningEffect", true);
		BindCB(0.f, 0.f, 0.f, 1.f);*/
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

}


