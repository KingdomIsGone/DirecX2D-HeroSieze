#include "ssBossHpFill.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssCamera.h"

namespace ss
{
	BossHpFill::BossHpFill()
		: mFullHpScale(1.74f)
		, mCurHpScale(1.74f)
		, mCurHP(10000.0f)
		, mPrevHP(10000.0f)
		, mFullHP(10000.0f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(mCurHpScale, 0.03f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		
		mTransform->SetPosition(pos);
		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));

		mWidth = Resources::Find<Texture>(L"EnemyHpBarFillRedTex")->GetWidth() / 6.f * 10.5f;
		mHpChanged = true;
	}
	BossHpFill::~BossHpFill()
	{
	}
	void BossHpFill::Initialize()
	{
		GameObject::Initialize();
	}
	void BossHpFill::Update()
	{
		GameObject::Update();

		float ratio = mCurHP / mFullHP;
		mCurHpScale = mFullHpScale * ratio;

		if (mCurHP != mPrevHP)
		{
			mHpChanged = true;
			mPrevHP = mCurHP;
		}

		if (mHpChanged)
		{
			Vector3 pos = mTransform->GetPosition();
			float ratio = mCurHpScale / mFullHpScale;
			pos.x = 0.0f;
			pos.x -= (1 - ratio) * mWidth * 0.5f;
			mTransform->SetPosition(pos);
			

			mTransform->SetScale(Vector3(mCurHpScale, 0.03f, 1.0f));
			mHpChanged = false;
		}
	}
	void BossHpFill::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void BossHpFill::Render()
	{
		GameObject::Render();
	}
	void BossHpFill::SetBlank()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}
	void BossHpFill::SetMater()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"EnemyHpBarFillRedMater"));
	}
}
