#include "ssHydra.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssTime.h"
#include "ssFireAuraScript.h"
#include "ssHydraSensor.h"
#include "ssHydraScript.h"

namespace ss
{
	Hydra::Hydra()
		: mDuration(7.5f)
		, mStage(0)
	{
		SetName(L"Hydra");
		//mMScript = AddComponent<FireAuraScript>();

		mTransform = GetComponent<Transform>();

		//콜라이더 세팅
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::SpecialMonster);
		collider->SetSize(Vector2(0.18f, 0.2f));
		collider->SetCenter(Vector2(0.00f, -0.03f));

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		mAnimator = AddComponent<Animator>();

		//stand animation
		{
			std::shared_ptr<Texture> HydraStandDownTex
				= Resources::Load<Texture>(L"HydraStandDownTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraStand\\HydraDown.png");
			mAnimator->Create(L"HydraStandDown", HydraStandDownTex, Vector2(0.0f, 0.0f), Vector2(31.f, 47.f), 5);
			std::shared_ptr<Texture> HydraStandDownLeftTex
				= Resources::Load<Texture>(L"HydraStandDownLeftTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraStand\\HydraDownLeft.png");
			mAnimator->Create(L"HydraStandDownLeft", HydraStandDownLeftTex, Vector2(0.0f, 0.0f), Vector2(32.f, 45.f), 5);
			std::shared_ptr<Texture> HydraStandDownRightTex
				= Resources::Load<Texture>(L"HydraStandDownRightTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraStand\\HydraDownRight.png");
			mAnimator->Create(L"HydraStandDownRight", HydraStandDownRightTex, Vector2(0.0f, 0.0f), Vector2(32.f, 45.f), 5);
			std::shared_ptr<Texture> HydraStandLeftTex
				= Resources::Load<Texture>(L"HydraStandLeftTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraStand\\HydraLeft.png");
			mAnimator->Create(L"HydraStandLeft", HydraStandLeftTex, Vector2(0.0f, 0.0f), Vector2(34.f, 45.f), 5);
			std::shared_ptr<Texture> HydraStandRightTex
				= Resources::Load<Texture>(L"HydraStandRightTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraStand\\HydraRight.png");
			mAnimator->Create(L"HydraStandRight", HydraStandRightTex, Vector2(0.0f, 0.0f), Vector2(34.f, 45.f), 5);
			std::shared_ptr<Texture> HydraStandUpTex
				= Resources::Load<Texture>(L"HydraStandUpTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraStand\\HydraUp.png");
			mAnimator->Create(L"HydraStandUp", HydraStandUpTex, Vector2(0.0f, 0.0f), Vector2(31.f, 47.f), 5);
			std::shared_ptr<Texture> HydraStandUpLeftTex
				= Resources::Load<Texture>(L"HydraStandUpLeftTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraStand\\HydraUpLeft.png");
			mAnimator->Create(L"HydraStandUpLeft", HydraStandUpLeftTex, Vector2(0.0f, 0.0f), Vector2(32.f, 45.f), 5);
			std::shared_ptr<Texture> HydraStandUpRightTex
				= Resources::Load<Texture>(L"HydraStandUpRightTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraStand\\HydraUpRight.png");
			mAnimator->Create(L"HydraStandUpRight", HydraStandUpRightTex, Vector2(0.0f, 0.0f), Vector2(32.f, 45.f), 5);
		}

		//Atk animation
		{
			std::shared_ptr<Texture> HydraAtkDownTex
				= Resources::Load<Texture>(L"HydraAtkDownTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraAtk\\HydraDownAtk.png");
			mAnimator->Create(L"HydraAtkDown", HydraAtkDownTex, Vector2(0.0f, 0.0f), Vector2(31.f, 47.f), 5);

			std::shared_ptr<Texture> HydraAtkDownLeftTex
				= Resources::Load<Texture>(L"HydraAtkDownLeftTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraAtk\\HydraDownLeftAtk.png");
			mAnimator->Create(L"HydraAtkDownLeft", HydraAtkDownLeftTex, Vector2(0.0f, 0.0f), Vector2(32.f, 45.f), 5);

			std::shared_ptr<Texture> HydraAtkDownRightTex
				= Resources::Load<Texture>(L"HydraAtkDownRightTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraAtk\\HydraDownRIghtAtk.png");
			mAnimator->Create(L"HydraAtkDownRight", HydraAtkDownRightTex, Vector2(0.0f, 0.0f), Vector2(32.f, 45.f), 5);

			std::shared_ptr<Texture> HydraAtkLeftTex
				= Resources::Load<Texture>(L"HydraAtkLeftTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraAtk\\HydraLeftAtk.png");
			mAnimator->Create(L"HydraAtkLeft", HydraAtkLeftTex, Vector2(0.0f, 0.0f), Vector2(34.f, 45.f), 5);

			std::shared_ptr<Texture> HydraAtkRightTex
				= Resources::Load<Texture>(L"HydraAtkRightTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraAtk\\HydraRightAtk.png");
			mAnimator->Create(L"HydraAtkRight", HydraAtkRightTex, Vector2(0.0f, 0.0f), Vector2(34.f, 45.f), 5);

			std::shared_ptr<Texture> HydraAtkUpTex
				= Resources::Load<Texture>(L"HydraAtkUpTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraAtk\\HydraUpAtk.png");
			mAnimator->Create(L"HydraAtkUp", HydraAtkUpTex, Vector2(0.0f, 0.0f), Vector2(31.f, 47.f), 5);

			std::shared_ptr<Texture> HydraAtkUpLeftTex
				= Resources::Load<Texture>(L"HydraAtkUpLeftTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraAtk\\HydraUpLeftAtk.png");
			mAnimator->Create(L"HydraAtkUpLeft", HydraAtkUpLeftTex, Vector2(0.0f, 0.0f), Vector2(32.f, 45.f), 5);

			std::shared_ptr<Texture> HydraAtkUpRightTex
				= Resources::Load<Texture>(L"HydraAtkUpRightTex", L"..\\Resources\\Texture\\Skill\\Hydra\\HydraAtk\\HydraUpRightAtk.png");
			mAnimator->Create(L"HydraAtkUpRight", HydraAtkUpRightTex, Vector2(0.0f, 0.0f), Vector2(32.f, 45.f), 5);
		}


		mTransform->SetScale(Vector3(1.5f, 1.5f, 1.0));
		mAnimator->PlayAnimation(L"HydraStandDown", true);

		mSensor = new HydraSensor();
		mSensor->SetHydra(this);
		mSensor->GetScript()->SetHydra(this);
		AddOtherGameObject(mSensor, eLayerType::Monster);

	}
	Hydra::~Hydra()
	{
		mSensor->SetState(eState::Dead);
	}
	void Hydra::Initialize()
	{
		GameObject::Initialize();
	}
	void Hydra::Update()
	{
		GameObject::Update();

		mDuration -= 1.f * Time::DeltaTime();

		if (mDuration <= 0.f)
			SetState(eState::Dead);



	}
	void Hydra::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Hydra::Render()
	{
		GameObject::Render();
	}
}