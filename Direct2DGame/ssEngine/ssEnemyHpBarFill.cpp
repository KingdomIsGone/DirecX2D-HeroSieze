#include "ssEnemyHpBarFill.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssCamera.h"

namespace ss
{
	EnemyHpBarFill::EnemyHpBarFill()
		: mFullHpScale(0.14f)
		, mCurHpScale(0.14f)
		, mCurHP(1000.0f)
		, mFullHP(1000.0f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(mCurHpScale, 0.018f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		pos.y += 0.174f;
		pos.z -= 0.002f;
		mTransform->SetPosition(pos);
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"EnemyHpBarFillRedMater"));

		mWidth = Resources::Find<Texture>(L"EnemyHpBarFillRedTex")->GetWidth() / 6.f;

		mHpChanged = true;
	}
	EnemyHpBarFill::~EnemyHpBarFill()
	{
	}
	void EnemyHpBarFill::Initialize()
	{
		GameObject::Initialize();
	}
	void EnemyHpBarFill::Update()
	{
		GameObject::Update();

		float ratio = mCurHP / mFullHP;
		mCurHpScale = mFullHpScale * ratio;
		
		if (mHpChanged)
		{
			Vector3 pos = mTransform->GetPosition();
			float ratio = mCurHpScale / mFullHpScale;
			pos.x = 0.0f;
			pos.x -= (1 - ratio) * mWidth * 0.5f;
			mTransform->SetPosition(pos);

			mTransform->SetScale(Vector3(mCurHpScale, 0.018f, 1.0f));
			mHpChanged = false;
		}
	}
	void EnemyHpBarFill::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void EnemyHpBarFill::Render()
	{
		GameObject::Render();
	}
}

