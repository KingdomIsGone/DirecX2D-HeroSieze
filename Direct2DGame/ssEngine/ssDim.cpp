#include "ssDim.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

namespace ss
{
	Dim::Dim()
		: mRenderOn(false)
	{
		SetName(L"Cursor");
		mTransform = GetComponent<Transform>();

		mMr = AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Find<Material>(L"DimMater"));
		mTransform->SetScale(Vector3(8.f, 5.f, 0.8f));
		mTransform->SetPosition(Vector3::Zero);
	}
	Dim::~Dim()
	{
	}
	void Dim::Initialize()
	{
		GameObject::Initialize();
	}
	void Dim::Update()
	{
		GameObject::Update();
	}
	void Dim::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Dim::Render()
	{
		if (mRenderOn)
			GameObject::Render();
		else
			return;
	}
	void Dim::SetOnOff(bool is)
	{
		Vector3 pos = mTransform->GetPosition();

		if (is)
		{
			mRenderOn = true;
		}
		else
		{
			mRenderOn = false;
		}

	}
}
