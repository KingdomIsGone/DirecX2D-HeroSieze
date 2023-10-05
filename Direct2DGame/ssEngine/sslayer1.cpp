#include "sslayer1.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"

namespace ss
{
	layer1::layer1()
	{
		SetName(L"layer1");

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		Animator* at = AddComponent<Animator>();

		std::shared_ptr<Texture> Layer1Tex
			= Resources::Load<Texture>(L"Layer1Tex"
				, L"..\\Resources\\Texture\\TitleMenu\\Menu_Layer_1_spr\\layer1_1024_576_5.png");
		at->Create(L"Layer1", Layer1Tex, Vector2(0.0f, 0.0f), Vector2(1024.0f, 576.0f), 5);
		at->PlayAnimation(L"Layer1", true);

	}

	layer1::~layer1()
	{
	}
	void layer1::Initialize()
	{
		GameObject::Initialize();
	}
	void layer1::Update()
	{
		GameObject::Update();
	}
	void layer1::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void layer1::Render()
	{
		GameObject::Render();
	}
}

