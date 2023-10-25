#include "ssLvUpEffector.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssRenderer.h"
#include "ssPlayerScript.h"
#include "ssAudioClip.h"
#include "ssAudioSource.h"

namespace ss
{
	LvUpEffector::LvUpEffector()
	{
		SetName(L"LvUpEffector");

		mTransform = GetComponent<Transform>();
		mTransform->SetScale(10.f, 10.f, 1.f);
		mAnimator = AddComponent<Animator>();
		mAnimator->SetLarge(true);
		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"EffectAnimationMaterial"));

		mOffset.x = 0.02f;
		mOffset.y = 0.12f;

		//ani setting
		{
			std::shared_ptr<Texture> LvUpEffectTex
				= Resources::Load<Texture>(L"LvUpEffectTex", L"..\\Resources\\Texture\\Player\\LvEffect.png");
			mAnimator->Create(L"LvUpEffect", LvUpEffectTex, Vector2(0.0f, 0.0f), Vector2(136.f, 236.f), 16, Vector2::Zero, 0.05f);
			
			std::shared_ptr<Texture> BlankTex
				= Resources::Load<Texture>(L"BlankLvTex", L"..\\Resources\\Texture\\Blank.png");
			mAnimator->Create(L"BlankLv", BlankTex, Vector2(0.0f, 0.0f), Vector2(136.f, 236.f), 16, Vector2::Zero, 0.05f);
		}

		mState = eState::Waiting;

		GameObject* audioSpeaker = new GameObject();
		mAs = audioSpeaker->AddComponent<AudioSource>();
		mAs->SetClip(Resources::Load<AudioClip>(L"LvUpSnd", L"..\\Resources\\Sound\\LevelUp.wav"));
	}

	LvUpEffector::~LvUpEffector()
	{
	}
	void LvUpEffector::Initialize()
	{
		GameObject::Initialize();
	}
	void LvUpEffector::Update()
	{
		GameObject::Update();

		UINT dir = (UINT)PlayerScript::GetDirState();

		if (dir == 0)
		{
			mOffset.x = -0.04f;
			mOffset.y = 0.12f;
		}
		else if (dir == 1)
		{
			mOffset.x = 0.02f;
			mOffset.y = 0.12f;
		}
		else if (dir == 2)
		{
			mOffset.x = 0.04f;
			mOffset.y = 0.12f;
		}
		else if (dir == 3)
		{
			mOffset.x = -0.04f;
			mOffset.y = 0.12f;
		}

		Vector3 playerPos = PlayerScript::GetPlayerPos();
		playerPos.z += 0.01f;
		playerPos.x += mOffset.x;
		playerPos.y += mOffset.y;
		mTransform->SetPosition(playerPos);

		

		switch (mState)
		{
		case ss::LvUpEffector::eState::Waiting:
		{
			mOn = false;
			mAnimator->PlayAnimation(L"BlankLv", false);
		}
			break;
		case ss::LvUpEffector::eState::Play:
			PlayEffect();
			break;
		case ss::LvUpEffector::eState::Play2:
		{
			mOn = true;
			mAnimator->PlayAnimation(L"LvUpEffect", false);

			if (mAnimator->GetActiveAnimation()->IsComplete())
			{
				mAnimator->GetActiveAnimation()->Reset();
				mState = eState::Waiting;
			}
		}
			break;
		default:
			break;
		}
	}
	void LvUpEffector::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void LvUpEffector::Render()
	{
		if(mOn)
			GameObject::Render();
	}

	void LvUpEffector::Play()
	{
		mState = eState::Play;
	}

	void LvUpEffector::PlayEffect()
	{
		mAs->Play();
		mState = eState::Play2;
	}
}


