#include "ssDesertDungeon2.h"
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

namespace ss
{
	DesertDungeon2::DesertDungeon2()
	{
	}
	DesertDungeon2::~DesertDungeon2()
	{
	}
	void DesertDungeon2::Initialize()
	{
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"DesertDungeon2", L"..\\Resources\\Texture\\Map\\Act_3_Boss_Dungeon_2.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(spriteShader);
				spriteMaterial->SetTexture(texture);
				Resources::Insert(L"DesertDungeon2Mater", spriteMaterial);
			}
			GameObject* DesertDungeon
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.01f), eLayerType::Map);
			DesertDungeon->SetName(L"DesertDungeon2");

			MeshRenderer* mr = DesertDungeon->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"DesertDungeon2Mater"));
			//DesertField->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.01f));
			DesertDungeon->GetComponent<Transform>()->SetScale(Vector3(15.0f, 15.0f, 1.0f));
			DesertDungeon->AddComponent<CameraScript>();

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

	void DesertDungeon2::Update()
	{
		Scene::Update();
	}

	void DesertDungeon2::LateUpdate()
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

	void DesertDungeon2::Render()
	{
		Scene::Render();
	}
}

