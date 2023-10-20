#include "ssEndingScene.h"
#include "ssTitleScene.h"
#include "ssCamera.h"
#include "ssRenderer.h"
#include "ssPlayerCameraScript.h"
#include "ssCameraScript.h"
#include "ssCursor.h"
#include "ssAnimator.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssLight.h"
#include "ssTexture.h"

namespace ss
{
	EndingScene::EndingScene()
	{
	}
	EndingScene::~EndingScene()
	{
	}
	void EndingScene::Initialize()
	{
		Scene::Initialize();

		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Map, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* mMainCamera = camera->AddComponent<Camera>();
			renderer::cameras.push_back(mMainCamera);

			mMainCamera->TurnLayerMask(eLayerType::UI, false);
			
			mMainCamera->TurnLayerMask(eLayerType::Cursor, false);
			mMainCamera->TurnLayerMask(eLayerType::Inventory, false);
		}
		
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");

		GameObject* Back = new GameObject();
		AddGameObject(eLayerType::Monster, Back);

		Back->GetComponent<Transform>()->SetScale(7.f, 7.f, 1.0f);
		Back->GetComponent<Transform>()->SetPosition(0.0f, 0.0f, 1.28f);

		MeshRenderer* Backmr = Back->AddComponent<MeshRenderer>();
		Backmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		Backmr->SetMaterial(Resources::Find<Material>(L"EndingMater"));

		{
			GameObject* cat = new GameObject();
			AddGameObject(eLayerType::Monster, cat);

			cat->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.0f);
			cat->GetComponent<Transform>()->SetPosition(-2.1f, 0.f, 1.f);

			MeshRenderer* catmr = cat->AddComponent<MeshRenderer>();
			catmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			catmr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			Animator* catani = cat->AddComponent<Animator>();
			std::shared_ptr<Texture> catTex
				= Resources::Load<Texture>(L"catTex"
					, L"..\\Resources\\Texture\\cat1.png");
			catani->Create(L"cat", catTex, Vector2(0.0f, 0.0f), Vector2(62.0f, 60.0f), 6);
			catani->PlayAnimation(L"cat", true);
		}
		{
			GameObject* cat = new GameObject();
			AddGameObject(eLayerType::Map, cat);

			cat->GetComponent<Transform>()->SetScale(2.f, 2.f, 1.0f);
			cat->GetComponent<Transform>()->SetPosition(2.1f, 0.f, 1.f);

			MeshRenderer* catmr = cat->AddComponent<MeshRenderer>();
			catmr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			catmr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			Animator* catani = cat->AddComponent<Animator>();
			std::shared_ptr<Texture> catTex
				= Resources::Load<Texture>(L"cat2Tex"
					, L"..\\Resources\\Texture\\cat2.png");
			catani->Create(L"cat2", catTex, Vector2(0.0f, 0.0f), Vector2(62.0f, 60.0f), 6);
			catani->PlayAnimation(L"cat2", true);
		}
		//¶óÀÌÆ®
		{
			GameObject* light = new GameObject();
			light->SetName(L"Light");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.f, 1.f, 1.f, 1.0f));
		}
	}
	void EndingScene::Update()
	{
		Scene::Update();
	}
	void EndingScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void EndingScene::Render()
	{
		Scene::Render();
	}
	void EndingScene::OnEnter()
	{
		renderer::cameras.push_back(mMainCamera);
		renderer::cameras.push_back(mPlayerCamera);
		renderer::cameras.push_back(mMonUICamera);
		renderer::cameras.push_back(mUICamera);
		renderer::cameras.push_back(mCursorCamera);
		renderer::mainCamera = mCursorCamera;
	}
	void EndingScene::OnExit()
	{
	}
}

