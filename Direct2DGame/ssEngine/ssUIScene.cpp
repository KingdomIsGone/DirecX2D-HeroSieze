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
//#include "ssCursor.h"

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
		//TextureSetting(); 렌더러에서
		

		//Cursor* cursor = new Cursor;
		//AddGameObject(eLayerType::UI, cursor);

		{
			GameObject* player
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);
			player->SetName(L"Player");
			Collider2D* cd = player->AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.2f, 1.2f));


			const float pi = 3.141592f;
			float degree = pi / 8.0f;

			player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
			player->GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.5f, 1.0f));
			//player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));

			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> MoveDownTex
				= Resources::Load<Texture>(L"MoveDownTex", L"..\\Resources\\Texture\\Player\\Move\\MoveDown.png");

			std::shared_ptr<Texture> MoveUpTex
				= Resources::Load<Texture>(L"MoveUpTex", L"..\\Resources\\Texture\\Player\\Move\\MoveUp.png");

			std::shared_ptr<Texture> MoveRightTex
				= Resources::Load<Texture>(L"MoveRightTex", L"..\\Resources\\Texture\\Player\\Move\\MoveRight.png");

			std::shared_ptr<Texture> MoveLeftTex
				= Resources::Load<Texture>(L"MoveLeftTex", L"..\\Resources\\Texture\\Player\\Move\\MoveLeft.png");

			Animator* at = player->AddComponent<Animator>();
			at->Create(L"MoveDown", MoveDownTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 48.0f), 6);
			at->Create(L"MoveUp", MoveUpTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 48.0f), 6);
			at->Create(L"MoveRight", MoveRightTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);
			at->Create(L"MoveLeft", MoveLeftTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);

			player->AddComponent<PlayerScript>();
		}

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
	

		//Cursor
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Cursor1", L"..\\Resources\\Texture\\UI\\Cursor1.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(spriteShader);
				spriteMaterial->SetTexture(texture);
				Resources::Insert(L"Cursor1Mater", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Cursor2", L"..\\Resources\\Texture\\UI\\Cursor2.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(spriteShader);
				spriteMaterial->SetTexture(texture);
				Resources::Insert(L"Cursor2Mater", spriteMaterial);
			}
		}
		{
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
		}
		UI_Setting();
		//배경 z=1.1f
		{
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
			AddGameObject(eLayerType::Player, obj);
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
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();

		//Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));

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

	void UIScene::Update()
	{
		Scene::Update();
	}

	void UIScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void UIScene::Render()
	{
		Scene::Render();
	}
	void UIScene::UI_Setting()
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
	}
}