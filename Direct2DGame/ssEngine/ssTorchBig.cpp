#include "ssTorchBig.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"

namespace ss
{
	TorchBig::TorchBig()
	{
		Animator* animator = AddComponent<Animator>();
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		std::shared_ptr<Texture> TorchBigTex
			= Resources::Load<Texture>(L"TorchBigTex", L"..\\Resources\\Texture\\MapObject\\TorchBig22745.png");
		animator->Create(L"Torch", TorchBigTex, Vector2(0.0f, 0.0f), Vector2(22.0f, 74.0f), 5);
		animator->PlayAnimation(L"Torch", true);

		mTransform = GetComponent<Transform>();
	}
	TorchBig::~TorchBig()
	{
	}
	void TorchBig::Initialize()
	{
		GameObject::Initialize();
	}
	void TorchBig::Update()
	{
		GameObject::Update();
	}
	void TorchBig::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void TorchBig::Render()
	{
		GameObject::Render();
	}
}
