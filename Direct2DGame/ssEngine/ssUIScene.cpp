#include "ssUIScene.h"
#include "ssTransform.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssMesh.h"
#include "ssCameraScript.h"
#include "ssCamera.h"
#include "ssSceneManager.h"

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
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		//캐릭터 및 레벨창
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"CharacterCircle", L"..\\Resources\\Texture\\UI\\CharacterCircle.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"CharacterCircle0", spriteMateiral);
			}

			GameObject* obj = new GameObject();
			obj->SetName(L"CharacterCircle");
			AddGameObject(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"CharacterCircle0"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.7f, 1.4f, 1.01f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 1.0f));
			//obj->AddComponent<CameraScript>();

		}

		//HPMP Bar
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

			GameObject* obj = new GameObject();
			obj->SetName(L"HPMPBar");
			AddGameObject(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"HPMPMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-1.74f, 1.4f, 1.01f));
			obj->GetComponent<Transform>()->SetScale(Vector3(1.5f, 0.22f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		//USEITEMBox
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ItemUseTex", L"..\\Resources\\Texture\\UI\\ItemUse.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"ItemUseMater", spriteMateiral);
			}

			GameObject* obj = new GameObject();
			obj->SetName(L"ItemUseBox");
			AddGameObject(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"ItemUseMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.3f, 1.1f, 1.01f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.27f, 0.27f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		//SkillMenu
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"SkillMenuTex", L"..\\Resources\\Texture\\UI\\SkillMenu.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SkillMenuMater", spriteMateiral);
			}

			GameObject* obj = new GameObject();
			obj->SetName(L"SkillMenu");
			AddGameObject(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SkillMenuMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-1.92f, -1.42f, 1.01f));
			obj->GetComponent<Transform>()->SetScale(Vector3(2.34f, 0.72f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		//key
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ttex", L"..\\Resources\\Texture\\UI\\t.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"tMater", spriteMateiral);

				GameObject* obj = new GameObject();
				obj->SetName(L"t");
				AddGameObject(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"tMater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.33f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ctex", L"..\\Resources\\Texture\\UI\\c.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"cMater", spriteMateiral);

				GameObject* obj = new GameObject();
				obj->SetName(L"c");
				AddGameObject(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"cMater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.215f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"1tex", L"..\\Resources\\Texture\\UI\\1.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"1Mater", spriteMateiral);

				GameObject* obj = new GameObject();
				obj->SetName(L"1");
				AddGameObject(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"1Mater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-2.015f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"2tex", L"..\\Resources\\Texture\\UI\\2.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"2Mater", spriteMateiral);

				GameObject* obj = new GameObject();
				obj->SetName(L"2");
				AddGameObject(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"2Mater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-1.75f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"3tex", L"..\\Resources\\Texture\\UI\\3.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"3Mater", spriteMateiral);

				GameObject* obj = new GameObject();
				obj->SetName(L"3");
				AddGameObject(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"3Mater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-1.485f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"4tex", L"..\\Resources\\Texture\\UI\\4.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"4Mater", spriteMateiral);

				GameObject* obj = new GameObject();
				obj->SetName(L"4");
				AddGameObject(eLayerType::UI, obj);
				MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"4Mater"));
				obj->GetComponent<Transform>()->SetPosition(Vector3(-1.22f, -1.65f, 1.005f));
				obj->GetComponent<Transform>()->SetScale(Vector3(0.12f, 0.12f, 1.0f));
				//obj->AddComponent<CameraScript>();
			}
		}

		//MenuSet
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"MenuSet", L"..\\Resources\\Texture\\UI\\MenuSet.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"MenuSetMater", spriteMateiral);

			GameObject* obj = new GameObject();
			obj->SetName(L"MenuSet");
			AddGameObject(eLayerType::UI, obj);
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"MenuSetMater"));
			obj->GetComponent<Transform>()->SetPosition(Vector3(-2.27f, -1.53f, 1.005f));
			obj->GetComponent<Transform>()->SetScale(Vector3(0.25f, 0.25f, 1.0f));
			//obj->AddComponent<CameraScript>();
		}

		//배경
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

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			//camera->AddComponent<CameraScript>();
		}

		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();

		//Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));
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
}