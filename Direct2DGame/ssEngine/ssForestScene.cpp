#include "ssForestScene.h"
#include "ssTransform.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssMesh.h"
#include "ssCameraScript.h"
#include "ssCamera.h"
#include "ssSceneManager.h"
#include "ssObject.h"
#include "ssAnimator.h"
#include "ssPlayerScript.h"
#include "ssCursor.h"
#include "ssPlayer.h"
#include "ssRenderer.h"
#include "ssIndicator.h"
#include "ssCollisionManager.h"
#include "ssPlayerCameraScript.h"
#include "ssTorchBig.h"
#include "ssUIScene.h"
#include "ssWallCollider.h"
#include "ssDesertDoor.h"
#include "ssTreeMon.h"
#include "ssEnt.h"
#include "ssBear.h"
#include "ssAudioClip.h"
#include "ssAudioSource.h"

namespace ss
{
	ForestScene::ForestScene()
	{
	}
	ForestScene::~ForestScene()
	{
	}
	void ForestScene::Initialize()
	{
		//common
		{
			UIScene ui;
			ui.UI_Setting();

			Player* player = new Player();
			player->SetName(L"Player");
			AddGameObject(eLayerType::Player, player);
			player->GetComponent<Transform>()->SetPosition(Vector3(4.04f, 8.0f, 1.0f)); 

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
			CollisionManager::SetLayer(eLayerType::Player, eLayerType::Wall, true);
			CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Wall, true);

			//Main Camera
			{
				GameObject* camera = new GameObject();
				camera->SetName(L"MainCamera");
				AddGameObject(eLayerType::Map, camera);
				camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
				mMainCamera = camera->AddComponent<Camera>();
				renderer::cameras.push_back(mMainCamera);

				mMainCamera->TurnLayerMask(eLayerType::UI, false);
				mMainCamera->TurnLayerMask(eLayerType::Cursor, false);
				mMainCamera->TurnLayerMask(eLayerType::Inventory, false);
				mMainCamera->TurnLayerMask(eLayerType::Player, false);
				mMainCamera->TurnLayerMask(eLayerType::MonsterUI, false);
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

			//MonsterUI Camera
			{
				GameObject* camera = new GameObject();
				camera->SetName(L"MonsterUICamera");
				AddGameObject(eLayerType::MonsterUI, camera);
				camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
				mMonUICamera = camera->AddComponent<Camera>();
				renderer::cameras.push_back(mMonUICamera);

				mMonUICamera->DisableLayerMasks();
				mMonUICamera->TurnLayerMask(eLayerType::MonsterUI, true);

				camera->AddComponent<CameraScript>();
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



		//door
		DesertDoor* door = new DesertDoor();
		door->SetName(L"ForestDoor");
		door->GetComponent<Transform>()->SetPosition(-9.2f, -8.8f, 1.f);
		AddGameObject(eLayerType::Item, door);


		//배경 z=1.5f
		{
			std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ForestMap", L"..\\Resources\\Texture\\Map\\ForestMap.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"ForestMapMater", spriteMateiral);
			}

			GameObject* obj = new GameObject();
			obj->SetName(L"ForestMap");
			AddGameObject(eLayerType::Map, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"ForestMapMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.5f));
			obj->GetComponent<Transform>()->SetScale(Vector3(25.0f, 27.0f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}
		

		//Monster
		{
			Ent* mon1 = new Ent();
			mon1->GetComponent<Transform>()->SetPosition(3.27f, 6.f, 1.f);
			AddGameObject(eLayerType::Monster, mon1);
			
			Ent* mon2 = new Ent();
			mon2->SetItmeHave(1);
			mon2->GetComponent<Transform>()->SetPosition(3.77f, 6.f, 1.f);
			AddGameObject(eLayerType::Monster, mon2);
			
			TreeMon* mon3 = new TreeMon();
			mon3->GetComponent<Transform>()->SetPosition(2.f, 5.3f, 1.f);
			AddGameObject(eLayerType::Monster, mon3);
			
			TreeMon* mon4 = new TreeMon();
			mon4->GetComponent<Transform>()->SetPosition(2.f, 5.9f, 1.f);
			AddGameObject(eLayerType::Monster, mon4);

			TreeMon* mon5 = new TreeMon();
			mon5->GetComponent<Transform>()->SetPosition(3.45f, 1.1f, 1.f);
			AddGameObject(eLayerType::Monster, mon5);
			
			Ent* mon6 = new Ent();
			mon6->GetComponent<Transform>()->SetPosition(1.39f, 2.29f, 1.f);
			AddGameObject(eLayerType::Monster, mon6);
			
			Ent* mon7 = new Ent();
			mon7->GetComponent<Transform>()->SetPosition(1.89f, 1.89f, 1.f);
			AddGameObject(eLayerType::Monster, mon7);

			Ent* mon8 = new Ent();
			mon8->GetComponent<Transform>()->SetPosition(6.5f, 1.1f, 1.f);
			AddGameObject(eLayerType::Monster, mon8);
			
			Ent* mon9 = new Ent();
			mon9->GetComponent<Transform>()->SetPosition(5.3f, -3.f, 1.f);
			AddGameObject(eLayerType::Monster, mon9);
			
			Ent* mon10 = new Ent();
			mon10->GetComponent<Transform>()->SetPosition(3.8f, -1.98f, 1.f);
			AddGameObject(eLayerType::Monster, mon10);
			
			Ent* mon11 = new Ent();
			mon11->GetComponent<Transform>()->SetPosition(-7.93f, -8.26f, 1.f);
			AddGameObject(eLayerType::Monster, mon11);
			
			TreeMon* mon12 = new TreeMon();
			mon12->GetComponent<Transform>()->SetPosition(6.4f, 2.56f, 1.f);
			AddGameObject(eLayerType::Monster, mon12);
			
			TreeMon* mon13 = new TreeMon();
			mon13->GetComponent<Transform>()->SetPosition(0.f, -6.48f, 1.f);
			AddGameObject(eLayerType::Monster, mon13);
			
			TreeMon* mon14 = new TreeMon();
			mon14->GetComponent<Transform>()->SetPosition(-0.69f, -6.14f, 1.f);
			AddGameObject(eLayerType::Monster, mon14);
			
			Bear* mon15 = new Bear();
			mon15->SetItmeHave(1);
			mon15->GetComponent<Transform>()->SetPosition(2.8f, -3.78f, 1.f);
			AddGameObject(eLayerType::Monster, mon15);

		}

		//wall
		{
			WallCollider* wall1 = new WallCollider();
			wall1->GetComponent<Transform>()->SetPosition(Vector3(3.12f, 8.f, 1.f));
			wall1->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.7f, 1.f));
			AddGameObject(eLayerType::Wall, wall1);

			WallCollider* wall2 = new WallCollider();
			wall2->GetComponent<Transform>()->SetPosition(Vector3(4.9f, 7.7f, 1.f));
			wall2->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.7f, 1.f));
			AddGameObject(eLayerType::Wall, wall2);

			WallCollider* wall3 = new WallCollider();
			wall3->GetComponent<Transform>()->SetPosition(Vector3(3.79f, 3.27f, 1.f));
			wall3->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.7f, 1.f));
			AddGameObject(eLayerType::Wall, wall3);

			WallCollider* wall4 = new WallCollider();
			wall4->GetComponent<Transform>()->SetPosition(Vector3(5.48f, 5.53f, 1.f));
			wall4->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.7f, 1.f));
			AddGameObject(eLayerType::Wall, wall4);

			WallCollider* wall5 = new WallCollider();
			wall5->GetComponent<Transform>()->SetPosition(Vector3(0.f, 2.64f, 1.f));
			wall5->GetComponent<Transform>()->SetScale(Vector3(1.5f, 2.8f, 1.f));
			AddGameObject(eLayerType::Wall, wall5);

			WallCollider* wall6 = new WallCollider();
			wall6->GetComponent<Transform>()->SetPosition(Vector3(4.45f, 2.24f, 1.f));
			wall6->GetComponent<Transform>()->SetScale(Vector3(0.5f, 1.4f, 1.f));
			AddGameObject(eLayerType::Wall, wall6);

			WallCollider* wall7 = new WallCollider();
			wall7->GetComponent<Transform>()->SetPosition(Vector3(2.55f, -0.44f, 1.f));
			wall7->GetComponent<Transform>()->SetScale(Vector3(2.7f, 0.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall7);

			WallCollider* wall8 = new WallCollider();
			wall8->GetComponent<Transform>()->SetPosition(Vector3(0.05f, -4.01f, 1.f));
			wall8->GetComponent<Transform>()->SetScale(Vector3(0.8f, 1.7f, 1.f));
			AddGameObject(eLayerType::Wall, wall8);
			
			WallCollider* wall9 = new WallCollider();
			wall9->GetComponent<Transform>()->SetPosition(Vector3(4.0f, -0.7f, 1.f));
			wall9->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.7f, 1.f));
			AddGameObject(eLayerType::Wall, wall9);
			
			WallCollider* wall10 = new WallCollider();
			wall10->GetComponent<Transform>()->SetPosition(Vector3(4.28f, 0.32f, 1.f));
			wall10->GetComponent<Transform>()->SetScale(Vector3(1.1f, 0.5f, 1.f));
			AddGameObject(eLayerType::Wall, wall10);
			
			WallCollider* wall11 = new WallCollider();
			wall11->GetComponent<Transform>()->SetPosition(Vector3(-4.7f, -8.3f, 1.f));
			wall11->GetComponent<Transform>()->SetScale(Vector3(2.9f, 0.6f, 1.f));
			AddGameObject(eLayerType::Wall, wall11);
			
			WallCollider* wall12 = new WallCollider();
			wall12->GetComponent<Transform>()->SetPosition(Vector3(-3.29f, -5.99f, 1.f));
			wall12->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.7f, 1.f));
			AddGameObject(eLayerType::Wall, wall12);
			
			WallCollider* wall13 = new WallCollider();
			wall13->GetComponent<Transform>()->SetPosition(Vector3(-4.81f, -6.21f, 1.f));
			wall13->GetComponent<Transform>()->SetScale(Vector3(1.1f, 1.6f, 1.f));
			AddGameObject(eLayerType::Wall, wall13);
			
			WallCollider* wall14 = new WallCollider();
			wall14->GetComponent<Transform>()->SetPosition(Vector3(-1.88f, -5.58f, 1.f));
			wall14->GetComponent<Transform>()->SetScale(Vector3(1.2f, 0.8f, 1.f));
			AddGameObject(eLayerType::Wall, wall14);

		}

		GameObject* audioSpeaker = new GameObject();
		mAs = audioSpeaker->AddComponent<AudioSource>();
		mAs->SetClip(Resources::Load<AudioClip>(L"ForestBGM", L"..\\Resources\\Sound\\BGM\\ForestBGM.wav"));
		mAs->SetLoop(true);

	}

	void ForestScene::Update()
	{
		Scene::Update();



	}

	void ForestScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void ForestScene::Render()
	{
		Scene::Render();
	}

	void ForestScene::OnEnter()
	{
		renderer::cameras.push_back(mMainCamera);
		renderer::cameras.push_back(mPlayerCamera);
		renderer::cameras.push_back(mMonUICamera);
		renderer::cameras.push_back(mUICamera);
		renderer::cameras.push_back(mCursorCamera);
		renderer::mainCamera = mCursorCamera;

		mAs->Play();
	}

	void ForestScene::OnExit()
	{
		mAs->Stop();
	}

}
