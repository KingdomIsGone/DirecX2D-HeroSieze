#include "ssLeaves01.h"
#include "ssCollider2D.h"
#include "ssLeavesScript.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssConstantBuffer.h"
#include "ssRenderer.h"

namespace ss
{
	Leaves01::Leaves01()
		: mAlpha(1.f)
	{
		SetName(L"Leaves01");

		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Item);
		mCollider->SetSize(Vector2(0.12f, 0.14f));
		mCollider->SetCenter(Vector2(0.0f, 0.13f));
		mScript = AddComponent<LeavesScript>();
		mScript->SetLeaves(this);
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(13.f, 13.f, 1.f);
		

		Animator* at = AddComponent<Animator>();
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"AlphaAnimationMaterial"));

		std::shared_ptr<Texture> Leaves01Tex
			= Resources::Load<Texture>(L"Leaves01Tex", L"..\\Resources\\Texture\\Map\\leaves.png");

		at->SetLarge(true);
		at->Create(L"Leaves01", Leaves01Tex, Vector2(0.0f, 0.0f), Vector2(420.f, 362.0f), 1);
		BindCB(mAlpha);
		at->PlayAnimation(L"Leaves01", false);

	}
	Leaves01::~Leaves01()
	{
	}
	void Leaves01::Initialize()
	{
		GameObject::Initialize();
	}
	void Leaves01::Update()
	{
		GameObject::Update();

		
		//at->PlayAnimation(L"Leaves01", false);
	}
	void Leaves01::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Leaves01::Render()
	{
		GameObject::Render();
	}

	void Leaves01::BindCB(float alpha)
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
