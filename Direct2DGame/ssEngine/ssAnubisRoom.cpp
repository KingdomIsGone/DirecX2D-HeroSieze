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

			DesertSkeleton* deSkeleton3 = new DesertSkeleton();
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

			DesertSkeleton* deSkeleton7 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton7);
			deSkeleton7->GetComponent<Transform>()->SetPosition(3.86f, 2.1f, 1.02f);

			DesertSkeleton* deSkeleton8 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton8);
			deSkeleton8->GetComponent<Transform>()->SetPosition(4.9f, 1.8f, 1.02f);

			DesertSkeleton* deSkeleton9 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton9);
			deSkeleton9->GetComponent<Transform>()->SetPosition(4.57f, 1.f, 1.02f);

			DesertSkeleton* deSkeleton10 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton10);
			deSkeleton10->GetComponent<Transform>()->SetPosition(4.38f, -0.15f, 1.02f);

			DesertSkeleton* deSkeleton11 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton11);
			deSkeleton11->GetComponent<Transform>()->SetPosition(4.29f, -2.3f, 1.02f);

			DesertSkeleton* deSkeleton12 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton12);
			deSkeleton12->GetComponent<Transform>()->SetPosition(0.65f, 1.f, 1.02f);

			DesertSkeleton* deSkeleton13 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton13);
			deSkeleton13->GetComponent<Transform>()->SetPosition(-0.1f, 0.43f, 1.02f);

			DesertSkeleton* deSkeleton14 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton14);
			deSkeleton14->GetComponent<Transform>()->SetPosition(-0.82f, 1.6f, 1.02f);

			DesertSkeleton* deSkeleton15 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton15);
			deSkeleton15->GetComponent<Transform>()->SetPosition(2.76f, 4.68f, 1.02f);

			DesertSkeleton* deSkeleton16 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton16);
			deSkeleton16->GetComponent<Transform>()->SetPosition(-4.0f, 4.2f, 1.02f);

			DesertSkeleton* deSkeleton17 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton17);
			deSkeleton17->GetComponent<Transform>()->SetPosition(-5.0f, 5.2f, 1.02f);

			DesertSkeleton* deSkeleton18 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton18);
			deSkeleton18->GetComponent<Transform>()->SetPosition(-5.1f, 1.8f, 1.02f);

			DesertSkeleton* deSkeleton19 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton19);
			deSkeleton19->GetComponent<Transform>()->SetPosition(-4.0f, 1.1f, 1.02f);

			DesertSkeleton* deSkeleton20 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton20);
			deSkeleton20->GetComponent<Transform>()->SetPosition(-4.6f, -0.2f, 1.02f);

			DesertSkeleton* deSkeleton21 = new DesertSkeleton();
			AddGameObject(eLayerType::Monster, deSkeleton21);
			deSkeleton21->GetComponent<Transform>()->SetPosition(-4.5f, -2.3f, 1.02f);
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

		//배경 z=1.1f
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
			obj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.1f));
			obj->GetComponent<Transform>()->SetScale(Vector3(27.0f, 27.0f, 1.0f));
			//obj->AddComponent<CameraScript>();
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

}
