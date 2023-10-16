#include "ssP_HpSmallBarFill.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssCamera.h"
#include "ssPlayerScript.h"

namespace ss
{
	P_HpSmallBarFill::P_HpSmallBarFill()
		: mFullHpScale(0.2f)
		, mCurHpScale(0.2f)
		, mCurHP(3000.0f)
		, mFullHP(3000.0f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(mCurHpScale, 0.018f, 1.0f));
		
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"PlayerHpSmallBarFillRedMater"));

		mWidth = mTransform->GetWorldRightBottom().x - mTransform->GetWorldLeftBottom().x;

		mHpChanged = true;
	}
	P_HpSmallBarFill::~P_HpSmallBarFill()
	{
	}
	void P_HpSmallBarFill::Initialize()
	{
		GameObject::Initialize();
	}
	void P_HpSmallBarFill::Update()
	{
		GameObject::Update();

		Vector3 playerPos = PlayerScript::GetPlayerPos();
		playerPos.x += 0.018f + mModifyX;
		playerPos.y += 0.195f;
		playerPos.z = 0.91;

		mTransform->SetPosition(playerPos);

		float ratio = mCurHP / mFullHP;
		mCurHpScale = mFullHpScale * ratio;

		if (mHpChanged)
		{
			float ratio = mCurHpScale / mFullHpScale;
			mModifyX = 0.0f;
			mModifyX -= (1 - ratio) * mWidth * 0.5f;

			mTransform->SetScale(Vector3(mCurHpScale, 0.018f, 1.0f));
			mHpChanged = false;
		}
	}
	void P_HpSmallBarFill::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void P_HpSmallBarFill::Render()
	{
		GameObject::Render();
	}
}
