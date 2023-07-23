#include "ssDesertTownScene.h"
#include "ssTransform.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssMesh.h"
#include "ssCameraScript.h"
#include "ssCamera.h"
#include "ssSceneManager.h"
#include "ssGridScript.h"
#include "ssObject.h"
#include "ssRenderer.h"
#include "ssCollider2D.h"
#include "ssPlayerScript.h"
#include "ssCollisionManager.h"
#include "ssAnimator.h"
#include "ssUIScene.h"

namespace ss
{
	DesertTownScene::DesertTownScene()
	{
	}
	DesertTownScene::~DesertTownScene()
	{
	}
	void DesertTownScene::Initialize()
	{
		UIScene ui;
		ui.UI_Setting();
		SetName(L"TownMap");
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"TownMap", L"..\\Resources\\Texture\\Map\\DesertTownMap.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(spriteShader);
				spriteMaterial->SetTexture(texture);
				Resources::Insert(L"TownMapMater", spriteMaterial);
			}
			GameObject* TownMap
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.5f), eLayerType::Map);
			TownMap->SetName(L"TownMap");

			MeshRenderer* mr = TownMap->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"TownMapMater"));
			//TownMap->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.01f));
			TownMap->GetComponent<Transform>()->SetScale(Vector3(18.0f, 12.0f, 1.0f));
			TownMap->AddComponent<CameraScript>();
		}

		{
			GameObject* player
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);
			player->SetName(L"Player");
			player->GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.5f, 1.0f));

			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> MoveDownTex
				= Resources::Load<Texture>(L"MoveDownTex", L"..\\Resources\\Texture\\Player\\Move\\MoveDown.png");

			std::shared_ptr<Texture> MoveUpTex
				= Resources::Load<Texture>(L"MoveUpTex", L"..\\Resources\\Texture\\Player\\Move\\MoveUp.png");

			std::shared_ptr<Texture> MoveRightTex
				= Resources::Load<Texture>(L"MoveRightTex", L"..\\Resources\\Texture\\Player\\Move\\MoveRight.png");

			std::shared_ptr<Texture> MoveLeftTex
				= Resources::Load<Texture>(L"MoveLeftTex", L"..\\Resources\\Texture\\Player\\Move\\MoveLeft.png");

			Animator* at = player->AddComponent<Animator>();
			at->Create(L"MoveDown", MoveDownTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 48.0f), 6);
			at->Create(L"MoveUp", MoveUpTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 48.0f), 6);
			at->Create(L"MoveRight", MoveRightTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);
			at->Create(L"MoveLeft", MoveLeftTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);

			player->AddComponent<PlayerScript>();

		}

		Camera* cameraComp = nullptr;
		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			//camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
		}

		//Player Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::Player, true);
			camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
			//camera->AddComponent<CameraScript>();
		}
	}

	void DesertTownScene::Update()
	{
		Scene::Update();
	}

	void DesertTownScene::LateUpdate()
	{
		//윈도우 좌표계에서 월드 좌표계로 바꾸기 viewPort.Unproject
		Vector3 pos(600, 350, 0.0f);
		Vector3 pos2(600, 350, 1000.0f);
		Viewport viewport;
		viewport.width = 1200.0f;
		viewport.height = 700.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		pos = viewport.Unproject(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		pos2 = viewport.Unproject(pos2, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		//pos, pos2를 잇는 선분으로 ray cast로 마우스 피킹 구현(3D)

		Scene::LateUpdate();
	}

	void DesertTownScene::Render()
	{
		Scene::Render();
	}
}