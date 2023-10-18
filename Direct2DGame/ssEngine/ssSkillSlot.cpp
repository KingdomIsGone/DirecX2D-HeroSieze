#include "ssSkillSlot.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssRenderer.h"
#include "ssTime.h"

namespace ss
{
	SkillSlot::SkillSlot()
		: mCoolPercent(0.f)
		, mCoolSpeed(1.f)
	{
		mMeshRenderer = AddComponent<MeshRenderer>();
		mMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMeshRenderer->SetMaterial(Resources::Find<Material>(L"MeteorIconMater"));
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(0.24f, 0.24f, 1.0f);
	}
	SkillSlot::~SkillSlot()
	{
	}
	void SkillSlot::Initialize()
	{
		GameObject::Initialize();
	}
	void SkillSlot::Update()
	{
		GameObject::Update();

		if (mOnCool)
		{
			mCoolPercent -= mCoolSpeed * Time::DeltaTime();

			if (mCoolPercent <= 0.f)
			{
				mOnCool = false;
				mCoolPercent = 0.f;
			}
			BindCB();
		}


	}
	void SkillSlot::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void SkillSlot::Render()
	{
		GameObject::Render();
	}
	void SkillSlot::CoolTimeStart()
	{
		mOnCool = true;
		mCoolPercent = 1.0f;
	}
	void SkillSlot::BindCB()
	{
		ss::graphics::ConstantBuffer* cb
			= renderer::constantBuffer[(int)eCBType::CoolTime + mSlotNum];

		switch (mSlotNum)
		{
		case 0:
			renderer::CoolTimeCB data;
			data.coolTimePercent = mCoolPercent;
			cb->SetData(&data);
			break;
		case 1:
			renderer::CoolTimeCB2 data2;
			data2.coolTimePercent = mCoolPercent;
			cb->SetData(&data2);
			break;
		case 2:
			renderer::CoolTimeCB3 data3;
			data3.coolTimePercent = mCoolPercent;
			cb->SetData(&data3);
			break;
		case 3:
			renderer::CoolTimeCB4 data4;
			data4.coolTimePercent = mCoolPercent;
			cb->SetData(&data4);
			break;
		default:
			break;
		}

		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::VS);
	}
	void SkillSlot::SetMater(std::wstring name)
	{
		mMaterName = name;
		mMeshRenderer->SetMaterial(Resources::Find<Material>(mMaterName));
	}
	bool SkillSlot::GetReady()
	{
		if (mCoolPercent == 0.f)
			return true;
		else
			return false;

	}
}
