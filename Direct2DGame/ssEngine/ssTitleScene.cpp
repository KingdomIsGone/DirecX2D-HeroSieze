#include "ssTitleScene.h"
#include "ssCamera.h"
#include "ssRenderer.h"
#include "ssPlayerCameraScript.h"
#include "ssCameraScript.h"
#include "ssCursor.h"
#include "ssAnimator.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssLight.h"
#include "ssTexture.h"
#include "ssStartBtn.h"
#include "ssInput.h"
#include "ssSceneManager.h"

namespace ss
{
	TitleScene::TitleScene()
		: mTornadoNum(1)
	{
		//button
		mStBtn = new StartBtn();
		AddGameObject(eLayerType::UI, mStBtn);
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		mCursor = new Cursor();
		AddGameObject(eLayerType::Cursor, mCursor);

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		{
			GameObject* Layer1 = new GameObject();
			AddGameObject(eLayerType::Map, Layer1);

			Layer1->GetComponent<Transform>()->SetScale(12.0f, 13.0f, 1.0f);
			Layer1->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.5f);

			MeshRenderer* Layer1mr = Layer1->AddComponent<MeshRenderer>();
			Layer1mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Layer1mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			Animator* Layer1ani = Layer1->AddComponent<Animator>();
			Layer1ani->SetLarge(true);

			std::shared_ptr<Texture> Layer1Tex
				= Resources::Load<Texture>(L"Layer1Tex"
					, L"..\\Resources\\Texture\\TitleMenu\\Menu_Layer_1_spr\\layer1.png");
			Layer1ani->Create(L"Layer1", Layer1Tex, Vector2(0.0f, 0.0f), Vector2(1024.0f, 576.0f), 5);
			Layer1ani->PlayAnimation(L"Layer1", true);
		}
		{
			GameObject* Layer2 = new GameObject();
			AddGameObject(eLayerType::Map, Layer2);

			Layer2->GetComponent<Transform>()->SetScale(10.f, 10.0f, 1.0f);
			Layer2->GetComponent<Transform>()->SetPosition(0.3f, 0.f, 1.4f);

			MeshRenderer* Layer2mr = Layer2->AddComponent<MeshRenderer>();
			Layer2mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Layer2mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			Animator* Layer2ani = Layer2->AddComponent<Animator>();
			Layer2ani->SetLarge(true);
			std::shared_ptr<Texture> Layer2Tex
				= Resources::Load<Texture>(L"Layer2Tex"
					, L"..\\Resources\\Texture\\TitleMenu\\Menu_Layer_2_spr\\layer2Big.png");
			Layer2ani->Create(L"Layer2", Layer2Tex, Vector2(0.0f, 0.0f), Vector2(1024.0f, 576.0f), 6);
			Layer2ani->PlayAnimation(L"Layer2", true);
		}
		{
			GameObject* Layer3 = new GameObject();
			AddGameObject(eLayerType::Map, Layer3);

			Layer3->GetComponent<Transform>()->SetScale(16.0f, 10.0f, 1.0f);
			Layer3->GetComponent<Transform>()->SetPosition(-0.6f, -0.35f, 1.3f);

			MeshRenderer* Layer3mr = Layer3->AddComponent<MeshRenderer>();
			Layer3mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Layer3mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			Animator* Layer3ani = Layer3->AddComponent<Animator>();
			Layer3ani->SetLarge(true);
			std::shared_ptr<Texture> Layer3Tex
				= Resources::Load<Texture>(L"Layer3Tex"
					, L"..\\Resources\\Texture\\TitleMenu\\Menu_Layer_3_spr.png");
			Layer3ani->Create(L"Layer3", Layer3Tex, Vector2(0.0f, 0.0f), Vector2(1024.0f, 576.0f), 1);
			Layer3ani->PlayAnimation(L"Layer3", false);
		}
		{
			GameObject* Layer4 = new GameObject();
			AddGameObject(eLayerType::Map, Layer4);

			Layer4->GetComponent<Transform>()->SetScale(12.f, 12.f, 1.0f);
			Layer4->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.29f);

			MeshRenderer* Layer4mr = Layer4->AddComponent<MeshRenderer>();
			Layer4mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Layer4mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			Animator* Layer4ani = Layer4->AddComponent<Animator>();
			Layer4ani->SetLarge(true);
			std::shared_ptr<Texture> Layer4Tex
				= Resources::Load<Texture>(L"Layer4Tex"
					, L"..\\Resources\\Texture\\TitleMenu\\Menu_Layer_4_spr\\layer4.png");
			Layer4ani->Create(L"Layer4", Layer4Tex, Vector2(0.0f, 0.0f), Vector2(1024.0f, 576.0f), 8);
			Layer4ani->PlayAnimation(L"Layer4", true);
		}
		{
			GameObject* Layer5 = new GameObject();
			AddGameObject(eLayerType::Map, Layer5);

			Layer5->GetComponent<Transform>()->SetScale(12.f, 12.f, 1.0f);
			Layer5->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.291f);

			MeshRenderer* Layer5mr = Layer5->AddComponent<MeshRenderer>();
			Layer5mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Layer5mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			Animator* Layer5ani = Layer5->AddComponent<Animator>();
			Layer5ani->SetLarge(true);
			std::shared_ptr<Texture> Layer5Tex
				= Resources::Load<Texture>(L"Layer5Tex"
					, L"..\\Resources\\Texture\\TitleMenu\\Menu_Layer_5_spr.png");
			Layer5ani->Create(L"Layer5", Layer5Tex, Vector2(0.0f, 0.0f), Vector2(1024.0f, 576.0f), 1);
			Layer5ani->PlayAnimation(L"Layer5", true);
		}
		{
			GameObject* tornado = new GameObject();
			AddGameObject(eLayerType::Map, tornado);

			tornado->GetComponent<Transform>()->SetScale(10.f, 12.f, 1.0f);
			tornado->GetComponent<Transform>()->SetPosition(0.25f, -0.1f, 1.28f);

			MeshRenderer* tornadomr = tornado->AddComponent<MeshRenderer>();
			tornadomr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			tornadomr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			mTornadoAni = tornado->AddComponent<Animator>();
			mTornadoAni->SetLarge(true);
			std::shared_ptr<Texture> tornadoTex
				= Resources::Load<Texture>(L"tornadoTex"
					, L"..\\Resources\\Texture\\TitleMenu\\Tornado1.png");
			mTornadoAni->Create(L"tornado1", tornadoTex, Vector2(0.0f, 0.0f), Vector2(1024.0f, 576.0f), 13);
			std::shared_ptr<Texture> tornado2Tex
				= Resources::Load<Texture>(L"tornado2Tex"
					, L"..\\Resources\\Texture\\TitleMenu\\Tornado2.png");
			mTornadoAni->Create(L"tornado2", tornadoTex, Vector2(0.0f, 0.0f), Vector2(1024.0f, 576.0f), 12);
		}
		{
			GameObject* logo = new GameObject();
			AddGameObject(eLayerType::Map, logo);

			logo->GetComponent<Transform>()->SetScale(12.f, 12.f, 1.0f);
			logo->GetComponent<Transform>()->SetPosition(-1.7f, 1.f, 1.28f);

			MeshRenderer* logomr = logo->AddComponent<MeshRenderer>();
			logomr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			logomr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			Animator* logoani = logo->AddComponent<Animator>();
			logoani->SetLarge(true);
			std::shared_ptr<Texture> logoTex
				= Resources::Load<Texture>(L"logoTex"
					, L"..\\Resources\\Texture\\TitleMenu\\Menu_Logo_spr\\logo.png");
			logoani->Create(L"logo", logoTex, Vector2(0.0f, 0.0f), Vector2(250.0f, 155.0f), 5);
			logoani->PlayAnimation(L"logo", true);
		}

		

		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Map, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::cameras.push_back(cameraComp);

			cameraComp->TurnLayerMask(eLayerType::UI, false);
			//cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::Cursor, false);
			cameraComp->TurnLayerMask(eLayerType::Inventory, false);
			camera->AddComponent<CameraScript>();
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::UI, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::cameras.push_back(cameraComp);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
		}

		//Cursor Camera
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"CursorCameraTitle");
			AddGameObject(eLayerType::Cursor, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->SetName(L"CursorCameraTitle");
			renderer::cameras.push_back(cameraComp);
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::Cursor, true);
			renderer::mainCamera = cameraComp;
			camera->AddComponent<PlayerCameraScript>();
		}

		//¶óÀÌÆ®
		{
			GameObject* light = new GameObject();
			light->SetName(L"Light");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.f, 1.0f, 1.0f, 1.0f));
		}
	}
	void TitleScene::Update()
	{
		Scene::Update();

		if (mTornadoNum == 1)
		{
			mTornadoAni->PlayAnimation(L"tornado1", false);
		}
		else if (mTornadoNum == 2)
		{
			mTornadoAni->PlayAnimation(L"tornado2", false);
		}

		if (mTornadoAni->GetActiveAnimation()->IsComplete())
		{
			if (mTornadoNum == 1)
				mTornadoNum = 2;
			else if (mTornadoNum == 2)
				mTornadoNum = 1;
		}
		
		if (Input::GetKey(eKeyCode::LBUTTON))
		{
			Vector3 cursorPos = Cursor::GetPos();

			Transform* tr = mStBtn->GetComponent<Transform>();
			Vector2 LBpos = tr->GetWorldLeftBottom();
			Vector2 RTpos = tr->GetWorldRightUp();

			if (LBpos.x <= cursorPos.x && cursorPos.x <= RTpos.x
				&& LBpos.y <= cursorPos.y && cursorPos.y <= RTpos.y)
			{
				mStBtn->SetClicked(true);
				SceneManager::LoadScene(L"UIScene");
			}
		}
		else
		{
			mStBtn->SetClicked(false);
		}

	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
		renderer::cameras.clear();
	}
}
