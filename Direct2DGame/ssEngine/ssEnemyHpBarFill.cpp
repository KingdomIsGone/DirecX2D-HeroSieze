#include "ssEnemyHpBarFill.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssCamera.h"

namespace ss
{
	UINT ss::EnemyHpBarFill::mCount = 0;
	EnemyHpBarFill::EnemyHpBarFill()
	{
		mTransform = GetComponent<Transform>();
		
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"EnemyHpBarFillRedMater"));

		mThisCount = mCount;
		mCount++;
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

		Vector3 ownerPos = mOwnerTransform->GetPosition();
		ownerPos.x += mOffsetX + mModifyX;
		ownerPos.y += mOffsetY;
		ownerPos.z -= 0.08f + 0.001f * mThisCount;

		mTransform->SetPosition(ownerPos);

		float ratio = mCurHP / mFullHP;
		mCurHpScale = mFullHpScale * ratio;
		
		if (mHpChanged)
		{
			
			float ratio = mCurHpScale / mFullHpScale;
			mModifyX = 0.0f;
			mModifyX -= (1 - ratio) * mWidth * 0.5f;

			mTransform->SetScale(Vector3(mCurHpScale, mScaleY, 1.0f));
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
	void EnemyHpBarFill::SetFullScale(float x, float y)
	{
		mFullHpScale = x;
		mCurHpScale = x;
		mScaleY = y;
		mTransform->SetScale(x, y, 1.f);
		float leftX = mTransform->GetWorldLeftBottom().x;
		float rightX = mTransform->GetWorldRightBottom().x;
		mWidth = rightX - leftX;
	}
}

