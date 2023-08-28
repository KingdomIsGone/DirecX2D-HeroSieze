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

		Player* player = new Player();
		AddGameObject(eLayerType::Player, player);
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 6.43f, 1.0f));

		cursor = new Cursor();
		AddGameObject(eLayerType::Cursor, cursor);

		Indicator* indicator = new Indicator();
		AddGameObject(eLayerType::Cursor, indicator);

		
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
			mBossHpFill->GetComponent<Transform>()->SetPosition(0.0f, 1.3f, 0.9f);
			mAnubis->SetBossHpFill(mBossHpFill);
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

		//TextureSetting();
		UI_Setting();

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

		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::cameras.push_back(cameraComp);

			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			camera->AddComponent<CameraScript>();
		}

		//Player Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::cameras.push_back(cameraComp);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::Player, true);
			camera->AddComponent<PlayerCameraScript>();
			//renderer::mainCamera = cameraComp;
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::cameras.push_back(cameraComp);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
		}

		//Cursor Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::cameras.push_back(cameraComp);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::Cursor, true);
			renderer::mainCamera = cameraComp;
			camera->AddComponent<PlayerCameraScript>();
		}

		//라이트
		{
			GameObject* light = new GameObject();
			light->SetName(L"Light");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
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
		}
		else
			mBossHpBar->SetBlank();

		if (mAnubis->GetDead())
			mBossHpBar->SetBlank();
	}

	void AnubisRoom::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void AnubisRoom::Render()
	{
		Scene::Render();
	}

	void AnubisRoom::UI_Setting()
	{
		//캐릭터 및 레벨창 z=1.01
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"CharacterCircle");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"CharacterCircle0"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.7f, 1.4f, 1.01f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		//HPMP Bar z=1.01
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"HPMPBar");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"HPMPMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-1.74f, 1.4f, 1.01f));
			obj->GetComponent<Transform>()->SetScale(Vector3(1.5f, 0.22f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		//USEITEMBox z=1.01
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"ItemUseBox");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"ItemUseMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.3f, 1.1f, 1.01f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.27f, 0.27f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		//SkillMenu z=1.01
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"SkillMenu");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SkillMenuMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-1.92f, -1.42f, 1.01f));
			obj->GetComponent<Transform>()->SetScale(Vector3(2.34f, 0.72f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		//key z=1.005
		{
			{
				GameObject* obj = new GameObject();
				obj->SetName(L"t");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"tMater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.33f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				GameObject* obj = new GameObject();
				obj->SetName(L"c");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"cMater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.215f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				GameObject* obj = new GameObject();
				obj->SetName(L"1");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"1Mater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.015f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				GameObject* obj = new GameObject();
				obj->SetName(L"2");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"2Mater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-1.75f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				GameObject* obj = new GameObject();
				obj->SetName(L"3");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"3Mater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-1.485f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				GameObject* obj = new GameObject();
				obj->SetName(L"4");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"4Mater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-1.22f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				GameObject* obj = new GameObject();
				obj->SetName(L"v");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"vMater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-0.97f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}
		}

		//MenuSet z=1.005
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"MenuSet");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"MenuSetMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.27f, -1.53f, 1.005f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.25f, 0.25f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		//ResourceBackBar z=1.005
		{
			{
				GameObject* obj = new GameObject();
				obj->SetName(L"ResourceBackBar1");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"ResourceBackBarMater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.70f, -1.35f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.4f, 0.058f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				GameObject* obj = new GameObject();
				obj->SetName(L"ResourceBackBar2");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"ResourceBackBarMater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.70f, -1.44f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.4f, 0.058f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				GameObject* obj = new GameObject();
				obj->SetName(L"ResourceBackBar3");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"ResourceBackBarMater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.70f, -1.53f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.4f, 0.058f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				GameObject* obj = new GameObject();
				obj->SetName(L"ResourceBackBar4");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"ResourceBackBarMater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.70f, -1.62f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.4f, 0.058f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}
		}

		//Portal z=1.006
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"TownPortal");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"TownPortalMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-0.97f, -1.53f, 1.006f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.15f, 1.0f));
			//obj->AddComponent<CameraScript>();  
		}


	}
	void AnubisRoom::TextureSetting()
	{
		//렌더링 LoadMaterial에서 세팅. 사용안하고 기록용
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		//캐릭터 및 레벨창 z=1.01
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"CharacterCircle", L"..\\Resources\\Texture\\UI\\CharacterCircle.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"CharacterCircle0", spriteMateiral);
			}
		}

		//HPMP Bar z=1.01
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"HPMPBarTex", L"..\\Resources\\Texture\\UI\\HpMpBar.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(spriteShader);
				spriteMaterial->SetTexture(texture);
				spriteMaterial->SetRenderingMode(eRenderingMode::CutOut);
				Resources::Insert(L"HPMPMater", spriteMaterial);
			}
		}

		//USEITEMBox z=1.01
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ItemUseTex", L"..\\Resources\\Texture\\UI\\ItemUse.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"ItemUseMater", spriteMateiral);
			}
		}

		//SkillMenu z=1.01
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"SkillMenuTex", L"..\\Resources\\Texture\\UI\\SkillMenu.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SkillMenuMater", spriteMateiral);
			}
		}

		//key z=1.005
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ttex", L"..\\Resources\\Texture\\UI\\t.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"tMater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ctex", L"..\\Resources\\Texture\\UI\\c.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"cMater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"1tex", L"..\\Resources\\Texture\\UI\\1.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"1Mater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"2tex", L"..\\Resources\\Texture\\UI\\2.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"2Mater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"3tex", L"..\\Resources\\Texture\\UI\\3.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"3Mater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"4tex", L"..\\Resources\\Texture\\UI\\4.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"4Mater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"vtex", L"..\\Resources\\Texture\\UI\\v.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"vMater", spriteMateiral);
			}
		}

		//MenuSet z=1.005
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"MenuSet", L"..\\Resources\\Texture\\UI\\MenuSet.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"MenuSetMater", spriteMateiral);
		}

		//ResourceBackBar z=1.005
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ResourceBackBar", L"..\\Resources\\Texture\\UI\\ResourceBackBar.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"ResourceBackBarMater", spriteMateiral);
			}
		}

		//Portal z=1.006
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"TownPortal", L"..\\Resources\\Texture\\UI\\Hud_Town_Portal_spr.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"TownPortalMater", spriteMateiral);
		}

		//Resource silverKey z=1.004
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"SilverKeyTex", L"..\\Resources\\Texture\\UI\\Hud_Key_spr.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"SilverKeyMater", spriteMateiral);
		}

		//Resource CrystalKey z=1.004
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"CrystalKeyTex", L"..\\Resources\\Texture\\UI\\Hud_Crystal_Key_spr.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"CrystalKeyMater", spriteMateiral);
		}
	}
}
