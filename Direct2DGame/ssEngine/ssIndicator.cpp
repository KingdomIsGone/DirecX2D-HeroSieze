#include "ssIndicator.h"
#include "ssMeshRenderer.h"
#include "ssAnimator.h"
#include "ssResources.h"

namespace ss
{
	Animator* ss::Indicator::mAnimator = nullptr;
	Vector3 ss::Indicator::mPos = {};

	Indicator::Indicator()
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.2f, 1.2f, 1.0f));

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> IndicaterTex
			= Resources::Load<Texture>(L"IndicaterTex", L"..\\Resources\\Texture\\Player\\Move\\Indicator43456.png");

		std::shared_ptr<Texture> BlankTex
			= Resources::Load<Texture>(L"BlankTex", L"..\\Resources\\Texture\\Blank.png");

		mAnimator = AddComponent<Animator>();
		mAnimator->Create(L"Indicator", IndicaterTex, Vector2(0.0f, 0.0f), Vector2(43.0f, 45.0f), 6);
		mAnimator->Create(L"Blank", BlankTex, Vector2(0.0f, 0.0f), Vector2(10.0f, 10.0f), 1);
		mAnimator->PlayAnimation(L"Blank", true);
	}
	Indicator::~Indicator()
	{
	}
	void Indicator::Initialize()
	{
		GameObject::Initialize();
	}
	void Indicator::Update()
	{
		GameObject::Update();

		if (mAnimator->GetActiveAnimation()->IsComplete())
			mAnimator->PlayAnimation(L"Blank", true);

		mTransform->SetPosition(mPos);
	}
	void Indicator::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Indicator::Render()
	{
		GameObject::Render();
	}
	void Indicator::aniPlay()
	{
		mAnimator->PlayAnimation(L"Indicator", false);
	}
}
