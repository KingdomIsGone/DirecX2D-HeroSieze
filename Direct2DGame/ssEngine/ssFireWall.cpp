#include "ssFireWall.h"
#include "ssPlayerScript.h"
#include "FireWallPiece.h"
#include "ssSceneManager.h"
#include "ssTime.h"
#include "ssAudioClip.h"
#include "ssAudioSource.h"
#include "ssResources.h"

namespace ss
{
	FireWall::FireWall(Vector3 cursorPos)
		: mDelayTime(0.0f)
		, mDistance(0.15f)
	{
		mStage = eStage::firstOne;
		Vector3 playerPos = PlayerScript::GetPlayerPos();
		mCursorPos = cursorPos;
		mCursorPos.z = 0.5f;
		
		Vector2 Cursor2Pos = Vector2(mCursorPos.x, mCursorPos.y);
		Vector2 Player2Pos = Vector2(playerPos.x, playerPos.y);
		mDegree = math::CalculateDegree(Player2Pos, Cursor2Pos);

		if ((mDegree <= 30.0f && -30.f < mDegree)
			|| (150.f < mDegree || mDegree <= -150.f))
			mCase = eDegreeCase::RightLeft;
		else if ((60.f < mDegree && mDegree <= 120.f)
			|| (-120.f < mDegree && mDegree <= -60.f))
			mCase = eDegreeCase::UpDown;
		else
			mCase = eDegreeCase::Ohter;

		mInclination = (playerPos.x - cursorPos.x) / (playerPos.y - cursorPos.y);
		mInclination = -1 / mInclination;

		mWallPos[0] = mCursorPos;
		switch (mCase)
		{
		case ss::FireWall::UpDown:
			mWallPos[1] = Vector3(mCursorPos.x - mDistance, mCursorPos.y, mCursorPos.z);
			mWallPos[2] = Vector3(mCursorPos.x + mDistance, mCursorPos.y, mCursorPos.z);
			mWallPos[3] = Vector3(mCursorPos.x - 2.f * mDistance, mCursorPos.y, mCursorPos.z);
			mWallPos[4] = Vector3(mCursorPos.x + 2.f * mDistance, mCursorPos.y, mCursorPos.z);
			mWallPos[5] = Vector3(mCursorPos.x - 3.f * mDistance, mCursorPos.y, mCursorPos.z);
			mWallPos[6] = Vector3(mCursorPos.x + 3.f * mDistance, mCursorPos.y, mCursorPos.z);
			break;
		
		case ss::FireWall::RightLeft:
			mWallPos[1] = Vector3(mCursorPos.x , mCursorPos.y - mDistance, mCursorPos.z);
			mWallPos[2] = Vector3(mCursorPos.x, mCursorPos.y + mDistance, mCursorPos.z);
			mWallPos[3] = Vector3(mCursorPos.x, mCursorPos.y - 2.f * mDistance, mCursorPos.z);
			mWallPos[4] = Vector3(mCursorPos.x, mCursorPos.y + 2.f * mDistance, mCursorPos.z);
			mWallPos[5] = Vector3(mCursorPos.x, mCursorPos.y - 3.f * mDistance, mCursorPos.z);
			mWallPos[6] = Vector3(mCursorPos.x, mCursorPos.y + 3.f * mDistance, mCursorPos.z);
			break;

		case ss::FireWall::Ohter:
			mWallPos[1] = Vector3(mCursorPos.x + mDistance, mCursorPos.y + mDistance * mInclination, mCursorPos.z);
			mWallPos[2] = Vector3(mCursorPos.x - mDistance, mCursorPos.y - mDistance * mInclination, mCursorPos.z);
			mWallPos[3] = Vector3(mCursorPos.x + 2.f * mDistance
				, mCursorPos.y + 2.f * mDistance * mInclination, mCursorPos.z);
			mWallPos[4] = Vector3(mCursorPos.x - 2.f * mDistance
				, mCursorPos.y - 2.f * mDistance * mInclination, mCursorPos.z);
			mWallPos[5] = Vector3(mCursorPos.x + 3.f * mDistance
				, mCursorPos.y + 3.f * mDistance * mInclination, mCursorPos.z);
			mWallPos[6] = Vector3(mCursorPos.x - 3.f * mDistance
				, mCursorPos.y - 3.f * mDistance * mInclination, mCursorPos.z);
			break;
		default:
			break;
		}

		GameObject* audioSpeaker = new GameObject();
		mAs = audioSpeaker->AddComponent<AudioSource>();
		mAs->SetClip(Resources::Load<AudioClip>(L"FireWallStart", L"..\\Resources\\Sound\\PlayerSound\\Fiewall_Start.wav"));

	}
	FireWall::~FireWall()
	{
	}
	void FireWall::Initialize()
	{
		GameObject::Initialize();
	}
	void FireWall::Update()
	{
		GameObject::Update();

		switch (mStage)
		{
		case ss::FireWall::eStage::firstOne:
			FirstOne();
			break;
		case ss::FireWall::eStage::delay1:
			Delay1();
			break;
		case ss::FireWall::eStage::firstTwo:
			FirstTwo();
			break;
		case ss::FireWall::eStage::delay2:
			Delay2();
			break;
		case ss::FireWall::eStage::secondTwo:
			SecondTwo();
			break;
		case ss::FireWall::eStage::delay3:
			Delay3();
			break;
		case ss::FireWall::eStage::ThirdTwo:
			ThirdTwo();
			break;
		case ss::FireWall::eStage::continueTime:
			ContinueTime();
			break;
		default:
			break;
		}

	}
	void FireWall::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void FireWall::Render()
	{
		GameObject::Render();
	}
	void FireWall::FirstOne()
	{
		mAs->SetClip(Resources::Find<AudioClip>(L"FireWallStart"));
		mAs->SetLoop(false);
		mAs->Play();

		mWalls[0] = new FireWallPiece();
		mWalls[0]->GetComponent<Transform>()->SetPosition(mWallPos[0]);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mWalls[0]);

		mStage = eStage::delay1;
	}
	void FireWall::Delay1()
	{
		mDelayTime += Time::DeltaTime();

		if (mDelayTime > 0.1f)
		{
			mStage = eStage::firstTwo;
			mDelayTime = 0.0f;
		}
	}
	void FireWall::FirstTwo()
	{
		mWalls[1] = new FireWallPiece();
		mWalls[1]->GetComponent<Transform>()->SetPosition(mWallPos[1]);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mWalls[1]);

		mWalls[2] = new FireWallPiece();
		mWalls[2]->GetComponent<Transform>()->SetPosition(mWallPos[2]);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mWalls[2]);
		mStage = eStage::delay2;
	}
	void FireWall::Delay2()
	{
		mDelayTime += Time::DeltaTime();

		if (mDelayTime > 0.08f)
		{
			mStage = eStage::secondTwo;
			mDelayTime = 0.0f;
		}
	}
	void FireWall::SecondTwo()
	{
		mWalls[3] = new FireWallPiece();
		mWalls[3]->GetComponent<Transform>()->SetPosition(mWallPos[3]);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mWalls[3]);

		mWalls[4] = new FireWallPiece();
		mWalls[4]->GetComponent<Transform>()->SetPosition(mWallPos[4]);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mWalls[4]);

		mStage = eStage::delay3;
	}
	void FireWall::Delay3()
	{
		mDelayTime += Time::DeltaTime();

		if (mDelayTime > 0.06f)
		{
			mStage = eStage::ThirdTwo;
			mDelayTime = 0.0f;
		}
	}
	void FireWall::ThirdTwo()
	{
		mWalls[5] = new FireWallPiece();
		mWalls[5]->GetComponent<Transform>()->SetPosition(mWallPos[5]);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mWalls[5]);

		mWalls[6] = new FireWallPiece();
		mWalls[6]->GetComponent<Transform>()->SetPosition(mWallPos[6]);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, mWalls[6]);

		mStage = eStage::continueTime;
	}
	void FireWall::ContinueTime()
	{
		if (!mAudioOnce)
		{
			mAs->SetClip(Resources::Find<AudioClip>(L"FireWallSound"));
			mAs->SetLoop(true);
			mAs->Play();
			mAudioOnce = true;
		}

		mDelayTime += Time::DeltaTime();

		if (mDelayTime < 5.0f)
			return;

		for (int i = 0; i < 7; i++)
		{
			mWalls[i]->SetState(eState::Dead);
		}

		mAs->Stop();
		SetState(eState::Dead);
	}
}