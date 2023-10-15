#include "ssSpearPiece.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"
#include "ssDamageScript.h"
#include "ssConstantBuffer.h"
#include "ssRenderer.h"

namespace ss
{
	float SpearPiece::mDamage = 10.0f;

	SpearPiece::SpearPiece()
		: mDeleteTime(0.0f)
		, mSpeed(3.0f)
		, mAlpha(1.f)
		, mMoveDistance(2.3f)
	{
		SetName(L"SpearPiece");
		AddComponent<DamageScript>();

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.2f, 1.2f, 1.0f));
		Animator* at = AddComponent<Animator>();
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"AlphaAnimationMaterial"));

		std::shared_ptr<Texture> SpearPieceTex
			= Resources::Load<Texture>(L"SpearPieceTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Valkyrie_Javelin_spr.png");

		at->Create(L"SpearPiece", SpearPieceTex, Vector2(0.0f, 0.0f), Vector2(9.f, 59.0f), 1);
		BindCB(mAlpha);
		at->PlayAnimation(L"SpearPiece", false);

		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Projectile);
		mCollider->SetSize(Vector2(0.07f, 0.35f));

	}
	SpearPiece::~SpearPiece()
	{
	}
	void SpearPiece::Initialize()
	{
		GameObject::Initialize();
	}
	void SpearPiece::Update()
	{
		GameObject::Update();

		Vector3 Pos = mTransform->GetPosition();

		if (mMoveDistance > 0.f)
		{
			mMoveDistance -= mSpeed * Time::DeltaTime();
			Pos.y -= mSpeed * Time::DeltaTime();
			mTransform->SetPosition(Pos);
		}
		else
		{
			mAlpha -= 0.5f * Time::DeltaTime();
			BindCB(mAlpha);
			if (mAlpha < 0)
				mAlpha = 0;
		}
		
	}

	void SpearPiece::LateUpdate()
	{
		GameObject::LateUpdate();

		mDeleteTime += Time::DeltaTime();

		if (mDeleteTime > 3.0f)
			SetState(eState::Dead);
	}
	void SpearPiece::Render()
	{
		GameObject::Render();
	}

	void SpearPiece::BindCB(float alpha)
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
