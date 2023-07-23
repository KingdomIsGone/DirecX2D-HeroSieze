#include "ssDesertDungeon1.h"
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

namespace ss
{
	DesertDungeon1::DesertDungeon1()
	{
	}
	DesertDungeon1::~DesertDungeon1()
	{
	}
	void DesertDungeon1::Initialize()
	{
		UIScene ui;
		ui.UI_Setting();
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"DesertDungeon1", L"..\\Resources\\Texture\\Map\\Act_3_Boss_Dungeon_1.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(spriteShader);
				spriteMaterial->SetTexture(texture);
				Resources::Insert(L"DesertDungeon1Mater", spriteMaterial);
			}
			GameObject* DesertField
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.5f), eLayerType::Map);
			DesertField->SetName(L"DesertDungeon1");

			MeshRenderer* mr = DesertField->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"DesertDungeon1Mater"));
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
	}

	void DesertDungeon1::Update()
	{
		Scene::Update();
	}

	void DesertDungeon1::LateUpdate()
	{
		//������ ��ǥ�迡�� ���� ��ǥ��� �ٲٱ� viewPort.Unproject
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
		//pos, pos2�� �մ� �������� ray cast�� ���콺 ��ŷ ����(3D)

		Scene::LateUpdate();
	}

	void DesertDungeon1::Render()
	{
		Scene::Render();
	}
}

