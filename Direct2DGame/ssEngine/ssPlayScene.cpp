#include "ssPlayScene.h"
#include "ssPlayScene.h"
#include "ssPlayScene.h"
#include "ssTransform.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssMesh.h"
#include "ssCameraScript.h"
#include "ssCamera.h"
#include "ssSceneManager.h"
#include "ssGridScript.h"
#include "ssObject.h"

namespace ss
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		{
			GameObject* player
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);
			player->SetName(L"Zelda");
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		

			GameObject* player2 = new GameObject();
			player2->SetName(L"ZeldaChild");
			AddGameObject(eLayerType::Player, player2);
			MeshRenderer* mr2 = player2->AddComponent<MeshRenderer>();
			mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			player2->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 1.0001f));

			player2->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());
			//player->AddComponent<CameraScript>();

			const float pi = 3.141592f;
			float degree = pi / 2.0f;

			player->GetComponent<Transform>()->SetPosition(Vector3(-3.0f, 0.0f, 1.0001f));
			player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Smile");
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			//player->AddComponent<CameraScript>();
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Smile");
			AddGameObject(eLayerType::UI, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.2f, 0.0f, 0.0f));
			//player->AddComponent<CameraScript>();
		}

		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
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


		{
			GameObject* grid = new GameObject();
			grid->SetName(L"Grid");
			AddGameObject(eLayerType::Grid, grid);
			MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
			GridScript* gridSc = grid->AddComponent<GridScript>();
			gridSc->SetCamera(cameraComp);
		}

		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();

		//Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		//Vector3 pos(600, 450, 0.0f);
		//Vector3 pos2(600, 450, 1000.0f);
		//Viewport viewport;
		//viewport.width = 1600.0f;
		//viewport.height = 900.0f;
		//viewport.x = 0;
		//viewport.y = 0;
		//viewport.minDepth = 0.0f;
		//viewport.maxDepth = 1.0f;

		//pos = viewport.Unproject(pos, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);
		//pos2 = viewport.Unproject(pos2, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);

		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}