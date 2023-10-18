#include "ssCloneAssault.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssRenderer.h"
#include "ssCloneScript.h"

namespace ss
{
	CloneAssault::CloneAssault(e4Direction dir)
		: mOffset(Vector3::Zero)
	{
		SetName(L"CloneAssault");

		mDir = dir;

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		Collider2D* col = AddComponent<Collider2D>();
		col->SetSize(Vector2(0.5f, 0.5f));

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"BossEffectMaterial3"));


		//ani setting
		{
			//melee
			std::shared_ptr<Texture> ValkAtkDownTex
				= Resources::Load<Texture>(L"ValkAtkDownTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Melee\\ValkAtkDown.png");
			mAnimator->Create(L"ValkAtkDown", ValkAtkDownTex, Vector2(0.0f, 0.0f), Vector2(92.f, 107.0f), 6, Vector2::Zero, 0.02f);

			std::shared_ptr<Texture> ValkAtkLeftTex
				= Resources::Load<Texture>(L"ValkAtkLeftTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Melee\\ValkAtkLeft.png");
			mAnimator->Create(L"ValkAtkLeft", ValkAtkLeftTex, Vector2(0.0f, 0.0f), Vector2(111.f, 83.0f), 6, Vector2::Zero, 0.02f);

			std::shared_ptr<Texture> ValkAtkRightTex
				= Resources::Load<Texture>(L"ValkAtkRightTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Melee\\ValkAtkRight.png");
			mAnimator->Create(L"ValkAtkRight", ValkAtkRightTex, Vector2(0.0f, 0.0f), Vector2(111.f, 83.0f), 6, Vector2::Zero, 0.02f);

			std::shared_ptr<Texture> ValkAtkUpTex
				= Resources::Load<Texture>(L"ValkAtkUpTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Melee\\ValkAtkUp.png");
			mAnimator->Create(L"ValkAtkUp", ValkAtkUpTex, Vector2(0.0f, 0.0f), Vector2(105.f, 92.0f), 6, Vector2::Zero, 0.02f);
		}

		BindCB(0.f, 0.f, 0.5f, 0.77f);

		mScript = AddComponent<CloneScript>();
		mScript->SetClone(this);
		mScript->SetDir(dir);
	}

	CloneAssault::~CloneAssault()
	{
		mScript = nullptr;
	}
	void CloneAssault::Initialize()
	{
		GameObject::Initialize();
	}
	void CloneAssault::Update()
	{
		GameObject::Update();
		
		//mPos = mTransform->GetPosition();
		
	}
	void CloneAssault::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void CloneAssault::Render()
	{
		GameObject::Render();
	}

	void CloneAssault::BindCB(float Radd, float Gadd, float Badd, float A)
	{
		ss::graphics::ConstantBuffer* cb
			= renderer::constantBuffer[(int)eCBType::BossEffect3];

		renderer::BossEffectCB3 data;

		data.Radd = Radd;
		data.Gadd = Gadd;
		data.Badd = Badd;
		data.A = A;
		

		cb->SetData(&data);

		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::VS);
	}

	void CloneAssault::SetStart()
	{
		if(mScript != nullptr)
			mScript->SetStart();

		
	}

	

}



