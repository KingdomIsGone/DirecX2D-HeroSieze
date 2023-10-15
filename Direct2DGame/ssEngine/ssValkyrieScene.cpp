#include "ssValkyrieScene.h"
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
#include "ssPlayerCameraScript.h"
#include "ssValkyrie.h"
#include "ssBossHpBar.h"
#include "ssBossHpFill.h"
#include "ssValAwaker.h"
#include "ssBossName.h"

namespace ss
{
	ValkyrieScene::ValkyrieScene()
	{
	}
	ValkyrieScene::~ValkyrieScene()
	{
	}
	void ValkyrieScene::Initialize()
	{
		//map texture
		{
			std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ValkyrieScene", L"..\\Resources\\Texture\\Map\\Act_8_Valkyrie.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(spriteShader);
				spriteMaterial->SetTexture(texture);
				Resources::Insert(L"ValkyrieSceneMater", spriteMaterial);
			}
			GameObject* DesertField
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.5f), eLayerType::Map);
			DesertField->SetName(L"ValkyrieScene");

			MeshRenderer* mr = DesertField->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"ValkyrieSceneMater"));
			//DesertField->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.01f));
			DesertField->GetComponent<Transform>()->SetScale(Vector3(22.5f, 24.0f, 1.0f));

		}

		//common
		{
			UIScene ui;
			ui.UI_Setting();

			Player* player = new Player();
			player->SetName(L"Player");
			AddGameObject(eLayerType::Player, player);
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.02f));

			Cursor* cursor = new Cursor();
			AddGameObject(eLayerType::Cursor, cursor);

			Indicator* indicator = new Indicator();
			AddGameObject(eLayerType::Cursor, indicator);

			CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
			CollisionManager::SetLayer(eLayerType::Player, eLayerType::Summon1, true);
			CollisionManager::SetLayer(eLayerType::Player, eLayerType::Summon2, true);
			CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Projectile, true);
			CollisionManager::SetLayer(eLayerType::Summon1, eLayerType::Projectile, true);
			CollisionManager::SetLayer(eLayerType::Summon2, eLayerType::Projectile, true);
			CollisionManager::SetLayer(eLayerType::Player, eLayerType::EnemyProjectile, true);
			CollisionManager::SetLayer(eLayerType::Summon1, eLayerType::Monster, true);
			CollisionManager::SetLayer(eLayerType::Summon2, eLayerType::Monster, true);
			CollisionManager::SetLayer(eLayerType::Summon1, eLayerType::Summon2, true);
			CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Monster, true);
			CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);

			//Main Camera
			{
				GameObject* camera = new GameObject();
				AddGameObject(eLayerType::Map, camera);
				camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
				mMainCamera = camera->AddComponent<Camera>();
				renderer::cameras.push_back(mMainCamera);

				mMainCamera->TurnLayerMask(eLayerType::UI, false);
				//cameraComp->TurnLayerMask(eLayerType::Player, false);
				mMainCamera->TurnLayerMask(eLayerType::Cursor, false);
				mMainCamera->TurnLayerMask(eLayerType::Inventory, false);
				camera->AddComponent<CameraScript>();
			}

			//Player Camera
			{
				GameObject* camera = new GameObject();
				camera->SetName(L"PlayerCamera");
				AddGameObject(eLayerType::Player, camera);
				camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
				mPlayerCamera = camera->AddComponent<Camera>();
				renderer::cameras.push_back(mPlayerCamera);
				mPlayerCamera->DisableLayerMasks();
				mPlayerCamera->TurnLayerMask(eLayerType::Player, true);
				camera->AddComponent<PlayerCameraScript>();
				//renderer::mainCamera = cameraComp;
			}

			//UI Camera
			{
				GameObject* camera = new GameObject();
				AddGameObject(eLayerType::UI, camera);
				camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
				mUICamera = camera->AddComponent<Camera>();
				renderer::cameras.push_back(mUICamera);
				mUICamera->DisableLayerMasks();
				mUICamera->TurnLayerMask(eLayerType::UI, true);
			}

			//Cursor Camera
			{
				GameObject* camera = new GameObject();
				camera->SetName(L"CursorCamera");
				AddGameObject(eLayerType::Cursor, camera);
				camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
				mCursorCamera = camera->AddComponent<Camera>();
				mCursorCamera->SetName(L"CursorCamera");
				renderer::cameras.push_back(mCursorCamera);
				mCursorCamera->DisableLayerMasks();
				mCursorCamera->TurnLayerMask(eLayerType::Cursor, true);
				renderer::mainCamera = mCursorCamera;
				camera->AddComponent<PlayerCameraScript>();
			}

			//Inventory Camera
			{
				GameObject* camera = new GameObject();
				AddGameObject(eLayerType::Inventory, camera);
				camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
				mInventoryCamera = camera->AddComponent<Camera>();
				mInventoryCamera->SetName(L"InventoryCamera");
				renderer::cameras.push_back(mInventoryCamera);
				mInventoryCamera->DisableLayerMasks();
				mInventoryCamera->TurnLayerMask(eLayerType::Inventory, true);
			}

			//라이트
			{
				GameObject* light = new GameObject();
				light->SetName(L"Light");
				AddGameObject(eLayerType::Light, light);
				Light* lightComp = light->AddComponent<Light>();
				lightComp->SetType(eLightType::Directional);
				lightComp->SetColor(Vector4(1.f, 1.0f, 1.0f, 1.0f));
			}
		}
		
		//boss, hpBar
		{
			mValkyrie = new Valkyrie();
			mValkyrie->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -1.0f, 1.0f));
			AddGameObject(eLayerType::Monster, mValkyrie);

			mBossHpBar = new BossHpBar();
			AddGameObject(eLayerType::UI, mBossHpBar);
			mBossHpBar->GetComponent<Transform>()->SetPosition(0.0f, 1.3f, 0.9f);

			mBossHpFill = new BossHpFill();
			AddGameObject(eLayerType::UI, mBossHpFill);
			mBossHpFill->GetComponent<Transform>()->SetPosition(0.0f, 1.3f, 0.89f);
			mBossHpFill->SetIniHp(20000.f);
			mValkyrie->SetBossHpFill(mBossHpFill);
		}

		mValAwaker = new ValAwaker();
		AddGameObject(eLayerType::Monster, mValAwaker);
		mValAwaker->GetComponent<Transform>()->SetPosition(0.0f, 2.5f, 1.f);
		
		mBossName = new BossName();
		mBossName->SetBossName(L"발키리");
		mBossName->SetFontPos(560.f, 20.f);
		AddGameObject(eLayerType::UI, mBossName);
		mBossName->GetComponent<Transform>()->SetPosition(0.0f, 0.f, 0.9f);
		
	}

	void ValkyrieScene::Update()
	{
		Scene::Update();

		if (mValAwaker->GetTouched())
			mValkyrie->SetAwake();

		if (mValkyrie->GetAwake())
		{
			mBossHpBar->SetHP();
			mBossHpFill->SetMater();
			mBossName->SetOnOff(true);
		}
		else
		{
			mBossHpBar->SetBlank();
			mBossName->SetOnOff(false);
		}

		if (mValkyrie->GetDead())
		{
			mBossHpBar->SetBlank();
			mBossName->SetOnOff(false);
		}
	}

	void ValkyrieScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void ValkyrieScene::Render()
	{
		Scene::Render();

	}
	void ValkyrieScene::OnEnter()
	{
		renderer::cameras.push_back(mMainCamera);
		renderer::cameras.push_back(mPlayerCamera);
		renderer::cameras.push_back(mUICamera);
		renderer::cameras.push_back(mCursorCamera);
		renderer::mainCamera = mCursorCamera;
	}
	void ValkyrieScene::OnExit()
	{
	}
}