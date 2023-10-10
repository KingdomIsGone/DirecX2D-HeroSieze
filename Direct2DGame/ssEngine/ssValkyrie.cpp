#include "ssValkyrie.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssValkyrieScript.h"
#include "ssValEffector.h"

namespace ss
{
	Valkyrie::Valkyrie()
		: mCurHp(500.0f)
		, mPrevHp(500.0f)
		, mTransformAniStage(0)
	{
		SetName(L"Valkyrie");

		mTransform = GetComponent<Transform>();

		//콜라이더 세팅
		GetComponent<Transform>()->SetScale(1.3f, 1.3f, 1.0f);
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::NormalMonster);
		collider->SetSize(Vector2(0.15f, 0.24f));
		collider->SetCenter(Vector2(-0.00f, 0.0f));

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		mAnimator = AddComponent<Animator>();

		//ani setting
		{
			//EventTransform
			std::shared_ptr<Texture> ValkWaitingTex
				= Resources::Load<Texture>(L"ValkWaitingTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\ValWating.png");
			mAnimator->Create(L"ValkWaiting", ValkWaitingTex, Vector2(0.0f, 0.0f), Vector2(108.f, 102.0f), 8);

			std::shared_ptr<Texture> ValkTurnTex
				= Resources::Load<Texture>(L"ValkTurnTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\ValTurn.png");
			mAnimator->Create(L"ValkTurn", ValkTurnTex, Vector2(0.0f, 0.0f), Vector2(108.f, 102.0f), 19);

			std::shared_ptr<Texture> ValkAfterTurnTex
				= Resources::Load<Texture>(L"ValkAfterTurnTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\valkAfterTurn.png");
			mAnimator->Create(L"ValkAfterTurn", ValkAfterTurnTex, Vector2(0.0f, 0.0f), Vector2(108.f, 102.0f), 8);

			std::shared_ptr<Texture> ValkTransformTex
				= Resources::Load<Texture>(L"ValkTransformTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\ValkTransform.png");
			mAnimator->Create(L"ValkTransform", ValkTransformTex, Vector2(0.0f, 0.0f), Vector2(108.f, 102.0f), 11);

			//Cast
			std::shared_ptr<Texture> ValkCastTex
				= Resources::Load<Texture>(L"ValkCastTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\ValkCast.png");
			mAnimator->Create(L"ValkCast", ValkCastTex, Vector2(0.0f, 0.0f), Vector2(105.f, 73.0f), 6);

			//Walk
			std::shared_ptr<Texture> ValkWalkDownTex
				= Resources::Load<Texture>(L"ValkWalkDownTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Walk\\ValWalkDown.png");
			mAnimator->Create(L"ValkWalkDown", ValkWalkDownTex, Vector2(0.0f, 0.0f), Vector2(108.f, 102.0f), 6);

			std::shared_ptr<Texture> ValkWalkLeftTex
				= Resources::Load<Texture>(L"ValkWalkLeftTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Walk\\ValWalkLeft.png");
			mAnimator->Create(L"ValkWalkLeft", ValkWalkLeftTex, Vector2(0.0f, 0.0f), Vector2(77.f, 85.0f), 6);

			std::shared_ptr<Texture> ValkWalkRightTex
				= Resources::Load<Texture>(L"ValkWalkRightTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Walk\\ValWalkRight.png");
			mAnimator->Create(L"ValkWalkRight", ValkWalkRightTex, Vector2(0.0f, 0.0f), Vector2(77.f, 85.0f), 6);

			std::shared_ptr<Texture> ValkWalkUpTex
				= Resources::Load<Texture>(L"ValkWalkUpTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Walk\\ValWalkUp.png");
			mAnimator->Create(L"ValkWalkUp", ValkWalkUpTex, Vector2(0.0f, 0.0f), Vector2(92.f, 91.0f), 6);

			//Melee
			std::shared_ptr<Texture> ValkAtkDownTex
				= Resources::Load<Texture>(L"ValkAtkDownTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Melee\\ValkAtkDown.png");
			mAnimator->Create(L"ValkAtkDown", ValkAtkDownTex, Vector2(0.0f, 0.0f), Vector2(92.f, 107.0f), 6);

			std::shared_ptr<Texture> ValkAtkLeftTex
				= Resources::Load<Texture>(L"ValkAtkLeftTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Melee\\ValkAtkLeft.png");
			mAnimator->Create(L"ValkAtkLeft", ValkAtkLeftTex, Vector2(0.0f, 0.0f), Vector2(111.f, 83.0f), 6);

			std::shared_ptr<Texture> ValkAtkRightTex
				= Resources::Load<Texture>(L"ValkAtkRightTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Melee\\ValkAtkRight.png");
			mAnimator->Create(L"ValkAtkRight", ValkAtkRightTex, Vector2(0.0f, 0.0f), Vector2(111.f, 83.0f), 6);

			std::shared_ptr<Texture> ValkAtkUpTex
				= Resources::Load<Texture>(L"ValkAtkUpTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Melee\\ValkAtkUp.png");
			mAnimator->Create(L"ValkAtkUp", ValkAtkUpTex, Vector2(0.0f, 0.0f), Vector2(105.f, 92.0f), 6);

			//Throw
			std::shared_ptr<Texture> ValkThrowDownTex
				= Resources::Load<Texture>(L"ValkThrowDownTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Throw\\ValkThrowDown.png");
			mAnimator->Create(L"ValkThrowDown", ValkThrowDownTex, Vector2(0.0f, 0.0f), Vector2(92.f, 84.0f), 6);

			std::shared_ptr<Texture> ValkThrowLeftTex
				= Resources::Load<Texture>(L"ValkThrowLeftTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Throw\\ValkThrowLeft.png");
			mAnimator->Create(L"ValkThrowLeft", ValkThrowLeftTex, Vector2(0.0f, 0.0f), Vector2(83.f, 83.0f), 6);

			std::shared_ptr<Texture> ValkThrowRightTex
				= Resources::Load<Texture>(L"ValkThrowRightTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Throw\\ValkThrowRight.png");
			mAnimator->Create(L"ValkThrowRight", ValkThrowRightTex, Vector2(0.0f, 0.0f), Vector2(83.f, 83.0f), 6);

			std::shared_ptr<Texture> ValkThrowUpTex
				= Resources::Load<Texture>(L"ValkThrowUpTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Throw\\ValkThrowUp.png");
			mAnimator->Create(L"ValkThrowUp", ValkThrowUpTex, Vector2(0.0f, 0.0f), Vector2(108.f, 82.0f), 6);

			std::shared_ptr<Texture> ValkThrowUpDownTex
				= Resources::Load<Texture>(L"ValkThrowUpDownTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Throw\\ValkThrowUpDown.png");
			mAnimator->Create(L"ValkThrowUpDown", ValkThrowUpDownTex, Vector2(0.0f, 0.0f), Vector2(92.f, 83.0f), 6);

			std::shared_ptr<Texture> ValkThrowUpLeftTex
				= Resources::Load<Texture>(L"ValkThrowUpLeftTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Throw\\ValkThrowUpLeft.png");
			mAnimator->Create(L"ValkThrowUpLeft", ValkThrowUpLeftTex, Vector2(0.0f, 0.0f), Vector2(77.f, 82.0f), 6);

			std::shared_ptr<Texture> ValkThrowUpRightTex
				= Resources::Load<Texture>(L"ValkThrowUpRightTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Throw\\ValkThrowUpRight.png");
			mAnimator->Create(L"ValkThrowUpRight", ValkThrowUpRightTex, Vector2(0.0f, 0.0f), Vector2(77.f, 82.0f), 6);

			std::shared_ptr<Texture> ValkThrowUpUpTex
				= Resources::Load<Texture>(L"ValkThrowUpUpTex", L"..\\Resources\\Texture\\Monster\\Valkyrie\\Throw\\ValkThrowUpUp.png");
			mAnimator->Create(L"ValkThrowUpUp", ValkThrowUpUpTex, Vector2(0.0f, 0.0f), Vector2(92.f, 92.0f), 6);
		
		}

		//mAnimator->PlayAnimation(L"ValkThrowUpRight", true);

		mScript = AddComponent<ValkyrieScript>();

		/*ValEffector* effector = new ValEffector();
		effector->GetComponent<Transform>()->SetParent(mTransform);
		AddOtherGameObject(effector, eLayerType::Projectile);*/

	}

	Valkyrie::~Valkyrie()
	{
	}
	void Valkyrie::Initialize()
	{
		GameObject::Initialize();
	}
	void Valkyrie::Update()
	{
		GameObject::Update();

		//PlayTransformAni();

		/*mCurHp = mScript->GetHP();
		if (mCurHp != mPrevHp)
		{
			mHpBarFill->ChangeHP(mCurHp);

			mPrevHp = mCurHp;
		}*/
	}
	void Valkyrie::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Valkyrie::Render()
	{
		GameObject::Render();
	}

	void Valkyrie::PlayTransformAni()
	{
		if (mTransformAniStage == 0)
		{
			mAnimator->PlayAnimation(L"ValkTurn", false);
			if (mAnimator->GetActiveAnimation()->IsComplete())
				mTransformAniStage = 1;
		}
		else if (mTransformAniStage == 1)
		{
			mAnimator->PlayAnimation(L"ValkAfterTurn", false);
			if (mAnimator->GetActiveAnimation()->IsComplete())
				mTransformAniStage = 2;
		}
		else if (mTransformAniStage == 2)
		{
			mAnimator->PlayAnimation(L"ValkTransform", false);
			if (mAnimator->GetActiveAnimation()->IsComplete())
				mTransformAniStage = 3;
		}


	}
	
}


