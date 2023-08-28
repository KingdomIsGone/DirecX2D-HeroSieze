#include "ssImmuneText.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssTime.h"

namespace ss
{
	ImmuneText::ImmuneText()
		: mDelayTime(0.0f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.3f, 0.2f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		pos.z -= 0.1f;
		pos.y -= 0.1f;
		mTransform->SetPosition(pos);

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}

	ImmuneText::~ImmuneText()
	{
	}

	void ImmuneText::Initialize()
	{
		GameObject::Initialize();
	}
	void ImmuneText::Update()
	{
		GameObject::Update();

		if (mbText)
		{
			SetTextMater();
			mDelayTime += Time::DeltaTime();
		}

		if (mDelayTime >= 1.5f)
		{
			mDelayTime = 0.0f;
			SetBlank();
			mbText = false;
		}
	}
	void ImmuneText::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void ImmuneText::Render()
	{
		GameObject::Render();
	}

	void ImmuneText::SetTextMater()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"ImmuneTextMater"));
	}

	void ImmuneText::SetBlank()
	{
		mRenderer->SetMaterial(Resources::Find<Material>(L"BlankMater"));
	}

}