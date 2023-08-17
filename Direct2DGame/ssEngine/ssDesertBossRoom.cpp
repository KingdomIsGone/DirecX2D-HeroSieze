#include "ssDesertBossRoom.h"
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
#include "ssUIScene.h"
#include "ssPlayer.h"
#include "ssCursor.h"
#include "ssIndicator.h"
#include "ssLight.h"

namespace ss
{
	DesertBossRoom::DesertBossRoom()
	{
	}
	DesertBossRoom::~DesertBossRoom()
	{
	}
	void DesertBossRoom::Initialize()
	{
		UIScene ui;
		ui.UI_Setting();
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"DesertBossRoom", L"..\\Resources\\Texture\\Map\\Boss_3_rm.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(spriteShader);
				spriteMaterial->SetTexture(texture);
				Resources::Insert(L"DesertBossRoomMater", spriteMaterial);
			}
			GameObject* DesertField
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.5f), eLayerType::Map);
			DesertField->SetName(L"DesertBossRoom");

			MeshRenderer* mr = DesertField->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"DesertBossRoomMater"));
			//DesertField->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.01f));
			DesertField->GetComponent<Transform>()->SetScale(Vector3(15.0f, 15.0f, 1.0f));
			DesertField->AddComponent<CameraScript>();

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

		//¶óÀÌÆ®
		{
			GameObject* light = new GameObject();
			light->SetName(L"Light");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			
		}

		Player* player = new Player();
		AddGameObject(eLayerType::Player, player);

		Cursor* cursor = new Cursor();
		AddGameObject(eLayerType::UI, cursor);

		Indicator* indicator = new Indicator();
		AddGameObject(eLayerType::UI, indicator);
	}

	void DesertBossRoom::Update()
	{
		Scene::Update();
	}

	void DesertBossRoom::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void DesertBossRoom::Render()
	{
		Scene::Render();
	}
}