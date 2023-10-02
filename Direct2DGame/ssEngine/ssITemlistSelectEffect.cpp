#include "ssITemlistSelectEffect.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

namespace ss
{
	ITemlistSelectEffect::ITemlistSelectEffect(GameObject* parent)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();
		Vector3 pos = mTransform->GetPosition();
		pos.z -= 0.2f;
		mTransform->SetPosition(pos);
		mTransform->SetScale(Vector3(1.55f, 0.7f, 1.f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
		mMaterName = L"ItemListSelectEffectMater";
	}

	ITemlistSelectEffect::~ITemlistSelectEffect()
	{
	}

	void ITemlistSelectEffect::Initialize()
	{
		GameObject::Initialize();
	}
	void ITemlistSelectEffect::Update()
	{
		GameObject::Update();

		if (mItemIn)
		{
			if(mSelected)
				SetMater();
		}
		else
			SetBlank();
		
		if(!mSelected)
			SetBlank();

	}
	void ITemlistSelectEffect::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void ITemlistSelectEffect::Render()
	{
		GameObject::Render();
	}

	void ITemlistSelectEffect::SetBlank()
	{
		//mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
		mRenderer->SetNoRender(true);
	}
	void ITemlistSelectEffect::SetMater()
	{
		mRenderer->SetNoRender(false);
		mRenderer->SetMaterial(Resources::Find<Material>(mMaterName));
	}
}
