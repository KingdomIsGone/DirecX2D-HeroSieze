#include "ssAnubisRoom.h"
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
#include "ssFireBall.h"
#include "ssIndicator.h"
#include "ssDesertSkeleton.h"
#include "ssCollisionManager.h"
#include "ssPlayerCameraScript.h"
#include "ssAnubis.h"
#include "ssChargedBolt.h"
#include "ssChainLightening.h"
#include "ssMummy.h"
#include "ssSarcophagus.h"
#include "ssBossHpBar.h"
#include "ssBossHpFill.h"
#include "ssTorchBig.h"
#include "ssBossName.h"
#include "ssUIScene.h"
#include "ssSkeletonMage.h"
#include "ssWallCollider.h"
#include "ssPortal.h"

namespace ss
{
	AnubisRoom::AnubisRoom()
	{
	}
	AnubisRoom::~AnubisRoom()
	{
	}
	void AnubisRoom::Initialize()
	{
		//common
		{
			UIScene ui;
			ui.UI_Setting();

			Player* player = new Player();
			player->SetName(L"Player");
			AddGameObject(eLayerType::Player, player);
			player->GetComponent<Transform>()->SetPosition(Vector3(0.13f, 6.38f, 1.0f));

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
		
		//skeleton
		{
			DesertSkeleton* deSkeleton = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton);
			deSkeleton->GetComponent<Transform>()->SetPosition(-0.1f, 4.5f, 1.02f);

			DesertSkeleton* deSkeleton1 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton1);
			deSkeleton1->GetComponent<Transform>()->SetPosition(-1.5f, 4.5f, 1.02f);

			DesertSkeleton* deSkeleton2 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton2);
			deSkeleton2->GetComponent<Transform>()->SetPosition(1.5f, 4.3f, 1.02f);

			SkeletonMage* deSkeleton3 = new SkeletonMage();
			AddGameObject(eLayerType::Monster, deSkeleton3);
			deSkeleton3->GetComponent<Transform>()->SetPosition(2.7f, 4.8f, 1.02f);

			DesertSkeleton* deSkeleton4 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton4);
			deSkeleton4->GetComponent<Transform>()->SetPosition(4.7f, 5.13f, 1.02f);

			DesertSkeleton* deSkeleton5 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton5);
			deSkeleton5->GetComponent<Transform>()->SetPosition(3.5f, 4.2f, 1.02f);

			DesertSkeleton* deSkeleton6 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton6);
			deSkeleton6->GetComponent<Transform>()->SetPosition(3.06f, 1.72f, 1.02f);

			SkeletonMage* deSkeleton7 = new SkeletonMage();
			AddGameObject(eLayerType::Monster, deSkeleton7);
			deSkeleton7->GetComponent<Transform>()->SetPosition(3.86f, 1.6f, 1.02f);

			DesertSkeleton* deSkeleton8 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton8);
			deSkeleton8->GetComponent<Transform>()->SetPosition(4.9f, 1.8f, 1.02f);

			DesertSkeleton* deSkeleton9 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton9);
			deSkeleton9->GetComponent<Transform>()->SetPosition(4.57f, 1.f, 1.02f);

			DesertSkeleton* deSkeleton10 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton10);
			deSkeleton10->GetComponent<Transform>()->SetPosition(4.38f, -0.15f, 1.02f);

			SkeletonMage* deSkeleton11 = new SkeletonMage();
			AddGameObject(eLayerType::Monster, deSkeleton11);
			deSkeleton11->GetComponent<Transform>()->SetPosition(4.29f, -2.3f, 1.02f);

			DesertSkeleton* deSkeleton12 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton12);
			deSkeleton12->GetComponent<Transform>()->SetPosition(0.65f, 1.f, 1.02f);

			
		}
		

		//boss
		{
			mAnubis = new Anubis();
			AddGameObject(eLayerType::Monster, mAnubis);
			mAnubis->GetComponent<Transform>()->SetPosition(-0.1f, -3.0f, 1.02f);

			mBossHpBar = new BossHpBar();
			AddGameObject(eLayerType::UI, mBossHpBar);
			mBossHpBar->GetComponent<Transform>()->SetPosition(0.0f, 1.3f, 0.9f);

			mBossHpFill = new BossHpFill();
			AddGameObject(eLayerType::UI, mBossHpFill);
			mBossHpFill->GetComponent<Transform>()->SetPosition(0.0f, 1.3f, 0.89f);
			mBossHpFill->SetIniHp(10000.f);
			mAnubis->SetBossHpFill(mBossHpFill);

			mBossName = new BossName();
			mBossName->SetBossName(L"아누비스");
			mBossName->SetFontPos(540.f, 20.f);
			AddGameObject(eLayerType::UI, mBossName);
			mBossName->GetComponent<Transform>()->SetPosition(0.0f, 0.f, 0.9f);
		}

		//torch
		{
			TorchBig* torch1 = new TorchBig();
			AddGameObject(eLayerType::Map, torch1);
			torch1->GetComponent<Transform>()->SetPosition(0.3f, 5.7f, 1.02f);
			TorchBig* torch2 = new TorchBig();
			AddGameObject(eLayerType::Map, torch2);
			torch2->GetComponent<Transform>()->SetPosition(-0.5f, 5.7f, 1.02f);

			TorchBig* torch3 = new TorchBig();
			AddGameObject(eLayerType::Map, torch3);
			torch3->GetComponent<Transform>()->SetPosition(0.4f, 2.3f, 1.02f);
			TorchBig* torch4 = new TorchBig();
			AddGameObject(eLayerType::Map, torch4);
			torch4->GetComponent<Transform>()->SetPosition(-0.6f, 2.3f, 1.02f);

			TorchBig* torch5 = new TorchBig();
			AddGameObject(eLayerType::Map, torch5);
			torch5->GetComponent<Transform>()->SetPosition(1.25f, -0.1f, 1.02f);
			TorchBig* torch6 = new TorchBig();
			AddGameObject(eLayerType::Map, torch6);
			torch6->GetComponent<Transform>()->SetPosition(-1.45f, -0.1f, 1.02f);

			TorchBig* torch7 = new TorchBig();
			AddGameObject(eLayerType::Map, torch7);
			torch7->GetComponent<Transform>()->SetPosition(-5.06f, 0.46f, 1.02f);
			TorchBig* torch8 = new TorchBig();
			AddGameObject(eLayerType::Map, torch8);
			torch8->GetComponent<Transform>()->SetPosition(-4.06f, 0.46f, 1.02f);

			TorchBig* torch9 = new TorchBig();
			AddGameObject(eLayerType::Map, torch9);
			torch9->GetComponent<Transform>()->SetPosition(4.84f, 0.46f, 1.02f);
			TorchBig* torch10 = new TorchBig();
			AddGameObject(eLayerType::Map, torch10);
			torch10->GetComponent<Transform>()->SetPosition(3.84f, 0.46f, 1.02f);
		}

		//배경 z=1.5f
		{
			std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"AnubisRoomTex", L"..\\Resources\\Texture\\Map\\AnubisRoom.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"AnubisRoomMater", spriteMateiral);
			}

			GameObject* obj = new GameObject();
			obj->SetName(L"AnubisBackground");
			AddGameObject(eLayerType::Map, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"AnubisRoomMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.5f));
			obj->GetComponent<Transform>()->SetScale(Vector3(27.0f, 27.0f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		//wall
		{
			WallCollider* wall1 = new WallCollider();
			wall1->GetComponent<Transform>()->SetPosition(Vector3(0.f, 6.83f, 1.f));
			wall1->GetComponent<Transform>()->SetScale(Vector3(6.f, 0.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall1);

			WallCollider* wall2 = new WallCollider();
			wall2->GetComponent<Transform>()->SetPosition(Vector3(-0.71f, 6.f, 1.f));
			wall2->GetComponent<Transform>()->SetScale(Vector3(0.3f, 1.8f, 1.f));
			AddGameObject(eLayerType::Wall, wall2);

			WallCollider* wall3 = new WallCollider();
			wall3->GetComponent<Transform>()->SetPosition(Vector3(0.51f, 6.f, 1.f));
			wall3->GetComponent<Transform>()->SetScale(Vector3(0.3f, 1.8f, 1.f));
			AddGameObject(eLayerType::Wall, wall3);

			WallCollider* wall4 = new WallCollider();
			wall4->GetComponent<Transform>()->SetPosition(Vector3(1.83f, 5.51f, 1.f));
			wall4->GetComponent<Transform>()->SetScale(Vector3(3.0f, 0.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall4);

			WallCollider* wall5 = new WallCollider();
			wall5->GetComponent<Transform>()->SetPosition(Vector3(4.28f, 6.18f, 1.f));
			wall5->GetComponent<Transform>()->SetScale(Vector3(1.3f, 1.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall5);

			WallCollider* wall6 = new WallCollider();
			wall6->GetComponent<Transform>()->SetPosition(Vector3(1.61f, 2.96f, 1.f));
			wall6->GetComponent<Transform>()->SetScale(Vector3(2.6f, 1.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall6);

			WallCollider* wall7 = new WallCollider();
			wall7->GetComponent<Transform>()->SetPosition(Vector3(5.6f, 4.92f, 1.f));
			wall7->GetComponent<Transform>()->SetScale(Vector3(0.3f, 3.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall7);

			WallCollider* wall8 = new WallCollider();
			wall8->GetComponent<Transform>()->SetPosition(Vector3(5.f, 3.87f, 1.f));
			wall8->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.5f, 1.f));
			AddGameObject(eLayerType::Wall, wall8);

			WallCollider* wall9 = new WallCollider();
			wall9->GetComponent<Transform>()->SetPosition(Vector3(3.76f, 3.52f, 1.f));
			wall9->GetComponent<Transform>()->SetScale(Vector3(1.8f, 0.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall9);

			WallCollider* wall10 = new WallCollider();
			wall10->GetComponent<Transform>()->SetPosition(Vector3(-1.84f, 2.96f, 1.f));
			wall10->GetComponent<Transform>()->SetScale(Vector3(2.4f, 1.4f, 1.f));
			AddGameObject(eLayerType::Wall, wall10);

			WallCollider* wall11 = new WallCollider();
			wall11->GetComponent<Transform>()->SetPosition(Vector3(-1.84f, 2.96f, 1.f));
			wall11->GetComponent<Transform>()->SetScale(Vector3(2.4f, 1.4f, 1.f));
			AddGameObject(eLayerType::Wall, wall11);

			WallCollider* wall12 = new WallCollider();
			wall12->GetComponent<Transform>()->SetPosition(Vector3(2.11f, 0.25f, 1.f));
			wall12->GetComponent<Transform>()->SetScale(Vector3(1.4f, 1.85f, 1.f));
			AddGameObject(eLayerType::Wall, wall12);

			WallCollider* wall13 = new WallCollider();
			wall13->GetComponent<Transform>()->SetPosition(Vector3(-2.36f, 0.44f, 1.f));
			wall13->GetComponent<Transform>()->SetScale(Vector3(1.2f, 1.55f, 1.f));
			AddGameObject(eLayerType::Wall, wall13);

			WallCollider* wall14 = new WallCollider();
			wall14->GetComponent<Transform>()->SetPosition(Vector3(-1.37f, 0.54f, 1.f));
			wall14->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.6f, 1.f));
			AddGameObject(eLayerType::Wall, wall14);

			WallCollider* wall15 = new WallCollider();
			wall15->GetComponent<Transform>()->SetPosition(Vector3(-0.27f, -0.61f, 1.f));
			wall15->GetComponent<Transform>()->SetScale(Vector3(3.f, 0.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall15);

			WallCollider* wall16 = new WallCollider();
			wall16->GetComponent<Transform>()->SetPosition(Vector3(4.34f, 2.92f, 1.f));
			wall16->GetComponent<Transform>()->SetScale(Vector3(3.f, 0.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall16);

			WallCollider* wall17 = new WallCollider();
			wall17->GetComponent<Transform>()->SetPosition(Vector3(6.f, 1.49f, 1.f));
			wall17->GetComponent<Transform>()->SetScale(Vector3(0.3f, 3.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall17);

			WallCollider* wall18 = new WallCollider();
			wall18->GetComponent<Transform>()->SetPosition(Vector3(5.36f, -1.8f, 1.f));
			wall18->GetComponent<Transform>()->SetScale(Vector3(0.9f, 4.0f, 1.f));
			AddGameObject(eLayerType::Wall, wall18);

			WallCollider* wall19 = new WallCollider();
			wall19->GetComponent<Transform>()->SetPosition(Vector3(3.1f, -1.18f, 1.f));
			wall19->GetComponent<Transform>()->SetScale(Vector3(1.5f, 3.0f, 1.f));
			AddGameObject(eLayerType::Wall, wall19);

			WallCollider* wall20 = new WallCollider();
			wall20->GetComponent<Transform>()->SetPosition(Vector3(3.7f, -3.7f, 1.f));
			wall20->GetComponent<Transform>()->SetScale(Vector3(2.5f, 0.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall20);

			WallCollider* wall21 = new WallCollider();
			wall21->GetComponent<Transform>()->SetPosition(Vector3(0.f, -1.45f, 1.f));
			wall21->GetComponent<Transform>()->SetScale(Vector3(5.f, 0.8f, 1.f));
			AddGameObject(eLayerType::Wall, wall21);

			WallCollider* wall22 = new WallCollider();
			wall22->GetComponent<Transform>()->SetPosition(Vector3(2.3f, -4.7f, 1.f));
			wall22->GetComponent<Transform>()->SetScale(Vector3(0.3f, 2.35f, 1.f));
			AddGameObject(eLayerType::Wall, wall22);

			WallCollider* wall23 = new WallCollider();
			wall23->GetComponent<Transform>()->SetPosition(Vector3(-0.27, -5.67f, 1.f));
			wall23->GetComponent<Transform>()->SetScale(Vector3(5.3f, 0.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall23);

			WallCollider* wall24 = new WallCollider();
			wall24->GetComponent<Transform>()->SetPosition(Vector3(-2.62, -3.4f, 1.f));
			wall24->GetComponent<Transform>()->SetScale(Vector3(0.3f, 5.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall24);










		}

		
	}

	void AnubisRoom::Update()
	{
		Scene::Update();

		Vector3 pos = cursor->GetPos();

		if (mAnubis->GetAwake())
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

		if (mAnubis->GetDead())
		{
			mBossHpBar->SetBlank();
			mBossName->SetOnOff(false);

			if (!mPortalOnce)
			{
				Portal* portal = new Portal();
				portal->GetComponent<Transform>()->SetPosition(Vector3(-0.12f, -2.24f, 1.1f));
				AddGameObject(eLayerType::Item, portal);
				mPortalOnce = true;
			}
		}
	}

	void AnubisRoom::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void AnubisRoom::Render()
	{
		Scene::Render();
	}

	void AnubisRoom::OnEnter()
	{
		renderer::cameras.push_back(mMainCamera);
		renderer::cameras.push_back(mPlayerCamera);
		renderer::cameras.push_back(mMonUICamera);
		renderer::cameras.push_back(mUICamera);
		renderer::cameras.push_back(mCursorCamera);
		renderer::mainCamera = mCursorCamera;
	}

	void AnubisRoom::OnExit()
	{
	}

}
