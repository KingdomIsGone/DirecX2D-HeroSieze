#include "ssThunderPiece.h"
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
	ThunderPiece::ThunderPiece(GameObject* parent)
		: mOffset(Vector3::Zero)
	{
		SetName(L"ThunderPiece");
		SetParent(parent);
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(1.f, 1.f, 1.f);
		mAnimator = AddComponent<Animator>();
		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> ThunderPieceTex
			= Resources::Load<Texture>(L"ThunderPieceTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Effect\\ThunderEffect.png");
		mAnimator->Create(L"ThunderPiece", ThunderPieceTex, Vector2(0.0f, 0.0f), Vector2(382.f, 34.f), 5);
		
		mAnimator->PlayAnimation(L"ThunderPiece", true);

	}

	ThunderPiece::~ThunderPiece()
	{
	}
	void ThunderPiece::Initialize()
	{
		GameObject::Initialize();
	}
	void ThunderPiece::Update()
	{
		GameObject::Update();


	}
	void ThunderPiece::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void ThunderPiece::Render()
	{
		GameObject::Render();
	}

	void ThunderPiece::BindCB(float Radd, float Gadd, float Badd, float A)
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

	void ThunderPiece::SetPosition(Vector3 pos)
	{
		mTransform->SetPosition(pos);
	}

	void ThunderPiece::SetRotation(Vector3 degree)
	{
		mTransform->SetRotation(degree);
	}

}



