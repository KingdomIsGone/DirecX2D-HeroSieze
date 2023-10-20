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
#include "ssLeaves01.h"
#include "ssTime.h"
#include "ssBear.h"
#include "ssWallCollider.h"
#include "ssAudioClip.h"
#include "ssAudioSource.h"

namespace ss
{
	ValkyrieScene::ValkyrieScene()
		: mCameraDistance(0.f)
		, mCWStage(0)
		, mEndTime(0.f)
	{
	}
	ValkyrieScene::~ValkyrieScene()
	{
	}
	void ValkyrieScene::Initialize()
	{
		//map texture, mapObject
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

			Leaves01* leaves01 = new Leaves01();
			leaves01->GetComponent<Transform>()->SetPosition(Vector3(1.f, -0.5f, 0.85f));
			AddGameObject(eLayerType::Player, leaves01);

			

		}

		//common
		{
			UIScene ui;
			ui.UI_Setting();

			Player* player = new Player();
			player->SetName(L"Player");
			AddGameObject(eLayerType::Player, player);
			player->GetComponent<Transform>()->SetPosition(Vector3(7.57f, -6.77f, 1.f));

			mPlayerScript = player->GetScript();

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
			CollisionManager::SetLayer(eLayerType::Player, eLayerType::Player, true);

			//Main Camera
			{
				mObjMainCamera = new GameObject();
				mObjMainCamera->SetName(L"MainCamera");
				AddGameObject(eLayerType::Map, mObjMainCamera);
				mObjMainCamera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
				mMainCamera = mObjMainCamera->AddComponent<Camera>();
				renderer::cameras.push_back(mMainCamera);

				mMainCamera->TurnLayerMask(eLayerType::UI, false);
				mMainCamera->TurnLayerMask(eLayerType::Player, false);
				mMainCamera->TurnLayerMask(eLayerType::Cursor, false);
				mMainCamera->TurnLayerMask(eLayerType::Inventory, false);
				mMainCamera->TurnLayerMask(eLayerType::MonsterUI, false);
				mObjMainCamera->AddComponent<CameraScript>();
			}

			//Player Camera
			{
				mObjPlayerCamera = new GameObject();
				mObjPlayerCamera->SetName(L"PlayerCamera");
				AddGameObject(eLayerType::Player, mObjPlayerCamera);
				mObjPlayerCamera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
				mPlayerCamera = mObjPlayerCamera->AddComponent<Camera>();
				renderer::cameras.push_back(mPlayerCamera);
				mPlayerCamera->DisableLayerMasks();
				mPlayerCamera->TurnLayerMask(eLayerType::Player, true);
				mPlayerCameraScirpt = mObjPlayerCamera->AddComponent<PlayerCameraScript>();
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
		
		//boss, hpBar
		{
			mValkyrie = new Valkyrie();
			mValkyrie->GetComponent<Transform>()->SetPosition(Vector3(-0.1f, 7.6f, 1.f));
			AddGameObject(eLayerType::Monster, mValkyrie);

			mBossHpBar = new BossHpBar();
			AddGameObject(eLayerType::UI, mBossHpBar);
			mBossHpBar->GetComponent<Transform>()->SetPosition(0.0f, 1.3f, 0.7f);

			mBossHpFill = new BossHpFill();
			AddGameObject(eLayerType::UI, mBossHpFill);
			mBossHpFill->GetComponent<Transform>()->SetPosition(0.0f, 1.3f, 0.69f);
			mBossHpFill->SetIniHp(20000.f);
			mValkyrie->SetBossHpFill(mBossHpFill);
		}

		mValAwaker = new ValAwaker();
		AddGameObject(eLayerType::Item, mValAwaker);
		mValAwaker->GetComponent<Transform>()->SetPosition(0.0f, 6.4f, 1.f);
		
		mBossName = new BossName();
		mBossName->SetBossName(L"발키리");
		mBossName->SetFontPos(560.f, 20.f);
		AddGameObject(eLayerType::UI, mBossName);
		mBossName->GetComponent<Transform>()->SetPosition(0.0f, 0.f, 0.9f);

		//monster Bear
		{
			Bear* bear1 = new Bear();
			bear1->SetItmeHave(2);
			bear1->GetComponent<Transform>()->SetPosition(2.24f, -2.89f, 1.f);
			AddGameObject(eLayerType::Monster, bear1);


			Bear* bear2 = new Bear();
			bear2->GetComponent<Transform>()->SetPosition(0.83f, -4.82f, 1.f);
			AddGameObject(eLayerType::Monster, bear2);
		}
		
		//WallCollider
		{
			WallCollider* wall1 = new WallCollider();
			wall1->GetComponent<Transform>()->SetPosition(Vector3(8.17f, -7.0f, 1.f));
			wall1->GetComponent<Transform>()->SetScale(Vector3(0.3f, 30.0f, 1.f));
			AddGameObject(eLayerType::Wall, wall1);

			WallCollider* wall2 = new WallCollider();
			wall2->GetComponent<Transform>()->SetPosition(Vector3(7.2f, -6.0f, 1.f));
			wall2->GetComponent<Transform>()->SetScale(Vector3(4.f, 0.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall2);

			WallCollider* wall3 = new WallCollider();
			wall3->GetComponent<Transform>()->SetPosition(Vector3(4.43f, -5.49f, 1.f));
			wall3->GetComponent<Transform>()->SetScale(Vector3(2.f, 0.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall3);

			WallCollider* wall4 = new WallCollider();
			wall4->GetComponent<Transform>()->SetPosition(Vector3(3.5f, -4.5f, 1.f));
			wall4->GetComponent<Transform>()->SetScale(Vector3(0.3f, 2.0f, 1.f));
			AddGameObject(eLayerType::Wall, wall4);

			WallCollider* wall5 = new WallCollider();
			wall5->GetComponent<Transform>()->SetPosition(Vector3(3.0f, -1.3f, 1.f));
			wall5->GetComponent<Transform>()->SetScale(Vector3(0.3f, 1.6f, 1.f));
			AddGameObject(eLayerType::Wall, wall5);

			WallCollider* wall6 = new WallCollider();
			wall6->GetComponent<Transform>()->SetPosition(Vector3(2.2f, 0.7f, 1.f));
			wall6->GetComponent<Transform>()->SetScale(Vector3(0.3f, 1.6f, 1.f));
			AddGameObject(eLayerType::Wall, wall6);

			WallCollider* wall7 = new WallCollider();
			wall7->GetComponent<Transform>()->SetPosition(Vector3(1.27f, 0.7f, 1.f));
			wall7->GetComponent<Transform>()->SetScale(Vector3(1.2f, 0.3f, 1.f));
			AddGameObject(eLayerType::Wall, wall7);

			WallCollider* wall8 = new WallCollider();
			wall8->GetComponent<Transform>()->SetPosition(Vector3(0.91f, 1.42f, 1.f));
			wall8->GetComponent<Transform>()->SetScale(Vector3(0.3f, 1.5f, 1.f));
			AddGameObject(eLayerType::Wall, wall8);

			WallCollider* wall9 = new WallCollider();
			wall9->GetComponent<Transform>()->SetPosition(Vector3(1.52f, 2.34f, 1.f));
			wall9->GetComponent<Transform>()->SetScale(Vector3(1.1f, 1.1f, 1.f));
			AddGameObject(eLayerType::Wall, wall9);

			WallCollider* wall10 = new WallCollider();
			wall10->GetComponent<Transform>()->SetPosition(Vector3(1.4f, 3.59f, 1.f));
			wall10->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.8f, 1.f));
			AddGameObject(eLayerType::Wall, wall10);

			WallCollider* wall11 = new WallCollider();
			wall11->GetComponent<Transform>()->SetPosition(Vector3(1.8f, 4.46f, 1.f));
			wall11->GetComponent<Transform>()->SetScale(Vector3(0.6f, 0.4f, 1.f));
			AddGameObject(eLayerType::Wall, wall11);

			WallCollider* wall12 = new WallCollider();
			wall12->GetComponent<Transform>()->SetPosition(Vector3(2.43f, 5.35f, 1.f));
			wall12->GetComponent<Transform>()->SetScale(Vector3(0.3f, 5.4f, 1.f));
			AddGameObject(eLayerType::Wall, wall12);

			WallCollider* wall13 = new WallCollider();
			wall13->GetComponent<Transform>()->SetPosition(Vector3(2.14f, 6.32f, 1.f));
			wall13->GetComponent<Transform>()->SetScale(Vector3(0.3f, 1.f, 1.f));
			AddGameObject(eLayerType::Wall, wall13);

			WallCollider* wall14 = new WallCollider();
			wall14->GetComponent<Transform>()->SetPosition(Vector3(1.65f, 7.f, 1.f));
			wall14->GetComponent<Transform>()->SetScale(Vector3(0.4f, 1.5f, 1.f));
			AddGameObject(eLayerType::Wall, wall14);

			WallCollider* wall15 = new WallCollider();
			wall15->GetComponent<Transform>()->SetPosition(Vector3(1.3f, 7.f, 1.f));
			wall15->GetComponent<Transform>()->SetScale(Vector3(0.4f, 0.8f, 1.f));
			AddGameObject(eLayerType::Wall, wall15);

			WallCollider* wall16 = new WallCollider();
			wall16->GetComponent<Transform>()->SetPosition(Vector3(0.93f, 8.23f, 1.f));
			wall16->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.9f, 1.f));
			AddGameObject(eLayerType::Wall, wall16);

			WallCollider* wall17 = new WallCollider();
			wall17->GetComponent<Transform>()->SetPosition(Vector3(-0.13f, 8.72f, 1.f));
			wall17->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.9f, 1.f));
			AddGameObject(eLayerType::Wall, wall17);

			WallCollider* wall18 = new WallCollider();
			wall18->GetComponent<Transform>()->SetPosition(Vector3(-1.03f, 8.69f, 1.f));
			wall18->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.9f, 1.f));
			AddGameObject(eLayerType::Wall, wall18);

			WallCollider* wall19 = new WallCollider();
			wall19->GetComponent<Transform>()->SetPosition(Vector3(-1.5f, 7.81f, 1.f));
			wall19->GetComponent<Transform>()->SetScale(Vector3(0.8f, 1.1f, 1.f));
			AddGameObject(eLayerType::Wall, wall19);

			WallCollider* wall20 = new WallCollider();
			wall20->GetComponent<Transform>()->SetPosition(Vector3(-2.65f, 6.86f, 1.f));
			wall20->GetComponent<Transform>()->SetScale(Vector3(1.2f, 1.1f, 1.f));
			AddGameObject(eLayerType::Wall, wall20);

			WallCollider* wall21 = new WallCollider();
			wall21->GetComponent<Transform>()->SetPosition(Vector3(-2.39f, 5.13f, 1.f));
			wall21->GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.8f, 1.f));
			AddGameObject(eLayerType::Wall, wall21);

			WallCollider* wall22 = new WallCollider();
			wall22->GetComponent<Transform>()->SetPosition(Vector3(-2.23f, 3.13f, 1.f));
			wall22->GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.8f, 1.f));
			AddGameObject(eLayerType::Wall, wall22);

			WallCollider* wall23 = new WallCollider();
			wall23->GetComponent<Transform>()->SetPosition(Vector3(-1.33f, 1.27f, 1.f));
			wall23->GetComponent<Transform>()->SetScale(Vector3(0.3f, 1.8f, 1.f));
			AddGameObject(eLayerType::Wall, wall23);



		}

		GameObject* audioSpeaker = new GameObject();
		mAs = audioSpeaker->AddComponent<AudioSource>();
		mAs->SetClip(Resources::Load<AudioClip>(L"ValkyrieBGM", L"..\\Resources\\Sound\\BGM\\ValBGM.wav"));
		mAs->SetClip(Resources::Load<AudioClip>(L"ValSceneBGM", L"..\\Resources\\Sound\\BGM\\ValSceneBGM.wav"));
		mAs->SetLoop(true);



	}

	void ValkyrieScene::Update()
	{
		Scene::Update();

		if (mValAwaker->GetTouched())
			mValkyrie->SetAwake();

		if (mValkyrie->GetAwake())
		{
			CameraWalkUp();
			if (!mSoundOnce)
			{
				mAs->Stop();
				mAs->SetClip(Resources::Find<AudioClip>(L"ValkyrieBGM"));
				mAs->SetLoop(true);
				mAs->Play();
				mSoundOnce = true;
			}
		}

		if (mValkyrie->GetEventComplete())
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
			mAs->Stop();
			mBossHpBar->SetBlank();
			mBossName->SetOnOff(false);

			mEndTime += Time::DeltaTime();
			if (mEndTime > 4.f)
				SceneManager::LoadScene(L"EndingScene");
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
		renderer::cameras.push_back(mMonUICamera);
		renderer::cameras.push_back(mUICamera);
		renderer::cameras.push_back(mCursorCamera);
		renderer::mainCamera = mCursorCamera;

		mAs->Play();
	}
	void ValkyrieScene::OnExit()
	{
	}
	void ValkyrieScene::CameraWalkUp()
	{
		if (mCWStage == 4)
			return;

		mPlayerScript->SetStop();

		if (mCWStage == 0)
		{
			PlayerScript::SetOnOff(false);
			mPlayerInitialPos = PlayerScript::GetPlayerPos();
			mCameraInitialPos = mObjMainCamera->GetComponent<Transform>()->GetPosition();
			mPlayerInitialCameraPos = mObjPlayerCamera->GetComponent<Transform>()->GetPosition();
			mCWStage++;
		}
		else if (mCWStage == 1)
		{
			if (mCameraDistance < 1.5f)
			{
				mCameraDistance += Time::DeltaTime();

				mMainCamera->TurnLayerMask(eLayerType::Player, false);
				mPlayerCameraScirpt->SetOnOff(false);

				Vector3 cameraPos = mObjMainCamera->GetComponent<Transform>()->GetPosition();
				Vector3 playerCameraPos = mObjPlayerCamera->GetComponent<Transform>()->GetPosition();

				playerCameraPos.y += Time::DeltaTime();
				cameraPos.y += Time::DeltaTime();

				mObjPlayerCamera->GetComponent<Transform>()->SetPosition(playerCameraPos);
				mObjMainCamera->GetComponent<Transform>()->SetPosition(cameraPos);
			}
			else
				mCWStage++;
		}
		else if (mCWStage == 2)
		{
			if (mValkyrie->GetEventComplete())
				mCWStage++;
		}
		else if (mCWStage == 3)
		{
			mMainCamera->TurnLayerMask(eLayerType::Player, true);
			mPlayerCameraScirpt->SetOnOff(true);
			mObjPlayerCamera->GetComponent<Transform>()->SetPosition(mPlayerInitialCameraPos);
			mObjMainCamera->GetComponent<Transform>()->SetPosition(mCameraInitialPos);
			PlayerScript::SetOnOff(true);
			mCWStage++;
		}
	}
	
}