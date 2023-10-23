#include "ssUIScene.h"
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
#include "ssCloneAssault.h"



namespace ss
{
	UIScene::UIScene()
	{
	}
	UIScene::~UIScene()
	{
	}
	void UIScene::Initialize()
	{
		Player* player = new Player();
		player->SetName(L"Player");
		AddGameObject(eLayerType::Player, player);
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.02f));

		cursor = new Cursor();
		AddGameObject(eLayerType::Cursor, cursor);

		Indicator* indicator = new Indicator();
		AddGameObject(eLayerType::Cursor, indicator);

		

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
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);

		//배경 z=1.1f
		{
			std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"TownHallTex", L"..\\Resources\\Texture\\TownHall.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"TownHallMater", spriteMateiral);
			}

			GameObject* obj = new GameObject();
			obj->SetName(L"TownhallBack");
			AddGameObject(eLayerType::Map, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"TownHallMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.1f));
			obj->GetComponent<Transform>()->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

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


		CloneAssault* clone = new CloneAssault(e4Direction::Up);
		clone->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 1.0f));
		
		AddGameObject(eLayerType::EnemyProjectile, clone);

	}

	void UIScene::Update()
	{
		Scene::Update();

		Vector3 pos = cursor->GetPos();
	}

	void UIScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void UIScene::Render()
	{
		Scene::Render();
	}
	void UIScene::OnEnter()
	{
		renderer::cameras.push_back(mMainCamera);
		renderer::cameras.push_back(mPlayerCamera);
		renderer::cameras.push_back(mUICamera);
		renderer::cameras.push_back(mCursorCamera);
		renderer::mainCamera = mCursorCamera;
	}
	void UIScene::OnExit()
	{
	}
	void UIScene::UI_Setting()
	{
		////맵프레임
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"MapFrame");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"MapFrameMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(2.5f, 1.25f, 0.75f));
			obj->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.f, 1.0f));
		}

		//캐릭터 및 레벨창 
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"CharacterCircle");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"CharacterCircle0"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.7f, 1.4f, 0.75f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}
		//head
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"pyroHead");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"PyroHead"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.7f, 1.42f, 0.745f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.16f, 0.16f, 1.0f));
		}

		//HPMP Bar z=1.01
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"HPMPBar");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"HPMPMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-1.74f, 1.4f, 0.75f));
			obj->GetComponent<Transform>()->SetScale(Vector3(1.5f, 0.22f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		////USEITEMBox z=1.01
		//{
		//	GameObject* obj = new GameObject();
		//	obj->SetName(L"ItemUseBox");
		//	AddGameObjectToActiveScene(eLayerType::UI, obj);
		//	MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"ItemUseMater"));
		//	obj->GetComponent<Transform>()->SetPosition(Vector3(-2.3f, 1.1f, 1.01f));
		//	obj->GetComponent<Transform>()->SetScale(Vector3(0.27f, 0.27f, 1.0f));
		//	//obj->AddComponent<CameraScript>();
		//}

		//SkillMenu z=1.01
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"SkillMenu");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SkillMenuMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-1.92f, -1.42f, 0.75f));
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
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.33f, -1.65f, 0.74f));
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
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.215f, -1.65f, 0.74f));
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
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.015f, -1.65f, 0.74f));
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
				obj->GetComponent<Transform>()->SetPosition(Vector3(-1.75f, -1.65f, 0.74f));
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
				obj->GetComponent<Transform>()->SetPosition(Vector3(-1.485f, -1.65f, 0.74f));
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
				obj->GetComponent<Transform>()->SetPosition(Vector3(-1.22f, -1.65f, 0.74f));
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
				obj->GetComponent<Transform>()->SetPosition(Vector3(-0.97f, -1.65f, 0.74f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}
		}

		//MenuSet z=0.745f
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"MenuSet");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"MenuSetMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.27f, -1.53f, 0.745f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.25f, 0.25f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		//ResourceBackBar z=0.745
		{
			{
				GameObject* obj = new GameObject();
				obj->SetName(L"ResourceBackBar1");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"ResourceBackBarMater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.70f, -1.35f, 0.745f));
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
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.70f, -1.44f, 0.745f));
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
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.70f, -1.53f, 0.745f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.4f, 0.058f, 1.0f));
			}

			{
				GameObject* obj = new GameObject();
				obj->SetName(L"ResourceBackBar4");
				AddGameObjectToActiveScene(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"ResourceBackBarMater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.70f, -1.62f, 0.745f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.4f, 0.058f, 1.0f));
			}
		}

		//ResourceIcon 0.74
		{
			GameObject* obj = new GameObject();
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"goldIconMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.85f, -1.35f, 0.74f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.085f, 0.075f, 1.0f));
		}
		{

			GameObject* obj = new GameObject();
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"rubyKeyIconMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.85f, -1.44f, 0.74f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.096f, 0.054f, 1.0f));
		}
		{

			GameObject* obj = new GameObject();
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"silverKeyIconMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.85f, -1.53f, 0.74f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.096f, 0.054f, 1.0f));
		}
		{

			GameObject* obj = new GameObject();
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"criKeyIconMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.85f, -1.62f, 0.74f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.096f, 0.054f, 1.0f));
		}


		//Portal z=1.006
		{
			GameObject* obj = new GameObject();
			obj->SetName(L"TownPortal");
			AddGameObjectToActiveScene(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"TownPortalMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-0.97f, -1.53f, 0.745f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.15f, 1.0f));
			//obj->AddComponent<CameraScript>();  
		}


	}
	void UIScene::TextureSetting()
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

		//헤드
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"head", L"..\\Resources\\Texture\\Player\\head.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"PyroHead", spriteMateiral);
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
