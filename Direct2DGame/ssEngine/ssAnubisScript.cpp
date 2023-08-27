#include "ssAnubisScript.h"
#include "ssTime.h"
#include "ssPlayerScript.h"
#include "ssGameObject.h"
#include "ssAnimator.h"
#include "ssChargedBolt.h"
#include "ssSceneManager.h"
#include < time.h >
#include "ssAnimator.h"
#include "ssResources.h"
#include "ssTexture.h"
#include "ssChainLightening.h"
#include "ssSarcophagus.h"

namespace ss
{
	UINT AnubisScript::mSarcoCount = 0;

	AnubisScript::AnubisScript()
		: mHp(100000.0f)
		, mChainStage(0)
		, mChainTime(0.0f)
		, mChainCount(0)
		, mPatternCount(0)
		, mPatternTime(4.0f)
	{
	}
	AnubisScript::~AnubisScript()
	{
	}
	void AnubisScript::Initialize()
	{
		mState = eState::Idle;
		mCoolTime = 0.0f;
		srand((unsigned int)time(NULL));

		mAnimator = GetOwner()->GetComponent<Animator>();
		mAnimator->PlayAnimation(L"Anubis_Down", true);

		mPos = GetOwner()->GetComponent<Transform>()->GetPosition();
	}
	void AnubisScript::Update()
	{
		mPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		if (mHp <= 0)
		{
			GetOwner()->SetState(GameObject::eState::Dead);
		}

		mCoolTime += Time::DeltaTime();

		switch (mState)
		{
		case ss::AnubisScript::eState::Sleep:
			break;
		case ss::AnubisScript::eState::Idle:
			Idle();
			break;
		case ss::AnubisScript::eState::ChargedBoltTwin:
			ChargedTwinBolts();
			break;
		case ss::AnubisScript::eState::ChainLight:
			ChainLightsTrifle();
			break;
		case ss::AnubisScript::eState::CreateSarco:
			CreateSarco();
			break;
		case ss::AnubisScript::eState::Dead:
			break;
		default:
			break;
		}

		//ChainLightsTrifle();

	}
	void AnubisScript::Idle()
	{
		mPatternTime += Time::DeltaTime();
		if(mAnimator->GetActiveAnimation()->IsComplete())
			mAnimator->PlayAnimation(L"Anubis_Down", true);

		if (mPatternTime >= 6.0f)
		{
			mPatternTime = 0.0f;
			mAnimator->PlayAnimation(L"Anubis_Cast", false);

			if (mPatternCount % 7 == 0)
			{
				mState = eState::CreateSarco;
				mPatternCount++;
			}
			else if (mPatternCount % 7 == 1)
			{
				ChargedBolts(false);
				mPatternCount++;
			}
			else if (mPatternCount % 7 == 2)
			{
				mState = eState::ChainLight;
				mPatternCount++;
			}
			else if (mPatternCount % 7 == 3)
			{
				mState = eState::ChargedBoltTwin;
				mPatternCount++;
			}
			else if (mPatternCount % 7 == 4)
			{
				ChargedBolts(true);
				mPatternCount++;
			}
			else if (mPatternCount % 7 == 5)
			{
				ChargedBolts(false);
				mPatternCount++;
			}
			else if (mPatternCount % 7 == 6)
			{
				mState = eState::ChainLight;
				mPatternCount++;
			}
			
		}

	}

	void AnubisScript::ChargedBolts(bool isVertical)
	{
		int num = rand() % 7;

		for (int i = 0; i < 30; i++)
		{
			if (i == num + 12 || i == num + 1 + 12 || i == num + 2 + 12)
				continue;

			ChargedBolt* bolt = new ChargedBolt(isVertical);
			Transform* Tr = bolt->GetComponent<Transform>();
			mPlayerPos = PlayerScript::GetPlayerPos();
			Vector3 pos = mPlayerPos;
			if (isVertical)
			{
				pos.y -= -4.35f + 0.3f * i;
				pos.x -= 2.2f;
			}
			else
			{
				pos.x += -4.35f + 0.3f * i;
				pos.y += 1.5f;
			}

			Tr->SetPosition(pos);

			SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, bolt);
		}
	}

	void AnubisScript::ChargedTwinBolts()
	{
		//mAnimator->PlayAnimation(L"Anubis_Cast", false);
		ChargedBolts(true);
		ChargedBolts(false);

		mState = eState::Idle;
	}

	void AnubisScript::ChainLights()
	{
		{
			mChainPos[0] = Vector3(mPos.x + 1.f, mPos.y + 1.f, 1.0f);
			mChainPos[1] = Vector3(mPos.x + 0.f, mPos.y - 1.f, 1.0f);
			mChainPos[2] = Vector3(mPos.x - 1.3f, mPos.y + 0.8f, 1.0f);
			mChainPos[3] = Vector3(mPos.x - 0.2f, mPos.y - 0.6f, 1.0f);
			mChainPos[4] = Vector3(mPos.x + 1.7f, mPos.y - 1.3f, 1.0f);
			mChainPos[5] = Vector3(mPos.x - 0.6f, mPos.y + 1.5f, 1.0f);
			mChainPos[6] = Vector3(mPos.x - 0.7f, mPos.y - 0.5f, 1.0f);
			mChainPos[7] = Vector3(mPos.x + 1.4f, mPos.y + 1.1f, 1.0f);
			mChainPos[8] = Vector3(mPos.x - 0.7f, mPos.y + 1.9f, 1.0f);
			mChainPos[9] = Vector3(mPos.x - 1.4f, mPos.y - 0.3f, 1.0f);
			mChainPos[10] = Vector3(mPos.x + 0.5f, mPos.y + 1.2f, 1.0f);
			mChainPos[11] = Vector3(mPos.x + 0.5f, mPos.y - 0.7f, 1.0f);
		}
		if (mChainStage == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				ChainLightening* chain = new ChainLightening();
				chain->GetComponent<Transform>()->SetPosition(mChainPos[i]);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, chain);
			}
			mChainStage = 1;
		}
		else if (mChainStage == 1)
		{
			for (int i = 4; i < 8; i++)
			{
				ChainLightening* chain = new ChainLightening();
				chain->GetComponent<Transform>()->SetPosition(mChainPos[i]);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, chain);
			}
			mChainStage = 2;
		}
		else if (mChainStage == 2)
		{
			for (int i = 8; i < 12; i++)
			{
				ChainLightening* chain = new ChainLightening();
				chain->GetComponent<Transform>()->SetPosition(mChainPos[i]);
				SceneManager::GetActiveScene()->AddGameObject(eLayerType::EnemyProjectile, chain);
			}
			mChainStage = 0;
		}
	}

	void AnubisScript::ChainLightsTrifle()
	{
		mChainTime += Time::DeltaTime();

		if (mChainTime > 0.5f)
		{
			ChainLights();
			mChainTime = 0.0f;
			mChainCount++;

			if (mChainCount == 2)
			{
				mChainCount = 0;
				mState = eState::Idle;
			}
		}
	}

	void AnubisScript::CreateSarco()
	{
		if (mSarcoCount != 0)
		{
			mState = eState::Idle;
			return;
		}

		mSarcoCount = 4;

		Sarcophagus* sarco = new Sarcophagus();
		sarco->SetDir(Sarcophagus::eDir::LeftBottom);
		sarco->GetComponent<Transform>()->SetPosition(mPos.x - 1.5f, mPos.y - 1.5f, mPos.z);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Summon1, sarco);

		Sarcophagus* sarco2 = new Sarcophagus();
		sarco2->SetDir(Sarcophagus::eDir::LeftTop);
		sarco2->GetComponent<Transform>()->SetPosition(mPos.x - 1.5f, mPos.y + 1.5f, mPos.z);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Summon1, sarco2);

		Sarcophagus* sarco3 = new Sarcophagus();
		sarco3->SetDir(Sarcophagus::eDir::RightTop);
		sarco3->GetComponent<Transform>()->SetPosition(mPos.x + 1.5f, mPos.y + 1.5f, mPos.z);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Summon1, sarco3);

		Sarcophagus* sarco4 = new Sarcophagus();
		sarco4->SetDir(Sarcophagus::eDir::RightBottom);
		sarco4->GetComponent<Transform>()->SetPosition(mPos.x + 1.5f, mPos.y - 1.5f, mPos.z);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Summon1, sarco4);

		mState = eState::Idle;
	}

	void AnubisScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void AnubisScript::OnCollisionStay(Collider2D* other)
	{
	}
	void AnubisScript::OnCollisionExit(Collider2D* other)
	{
	}
}