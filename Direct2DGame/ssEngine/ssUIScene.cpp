#include "ssUIScene.h"
#include "ssTransform.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssMesh.h"
#include "ssCameraScript.h"
#include "ssCamera.h"
#include "ssSceneManager.h"

namespace ss
{
	UIScene::UIScene()
	{
	}
	UIScene::~UIScene()
	{
	}
	void UIScene::Initialize()
	{
		{
			GameObject* player = new GameObject();
			player->SetName(L"CharacterCircle");
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"CharacterCircle0"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));
			//player->AddComponent<CameraScript>();

		}


		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			//camera->AddComponent<CameraScript>();
		}

		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();

		//Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));
	}

	void UIScene::Update()
	{
		Scene::Update();
	}

	void UIScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void UIScene::Render()
	{
		Scene::Render();
	}
}