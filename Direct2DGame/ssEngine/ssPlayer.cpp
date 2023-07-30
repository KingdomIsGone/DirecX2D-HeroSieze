#include "ssPlayer.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCamera.h"
#include "ssAnimator.h"
#include "ssPlayerScript.h"

namespace ss
{
	Player::Player()
	{
		mTransform = GetComponent<Transform>();
		AddComponent<PlayerScript>();

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		{
			SetName(L"Player");
			Collider2D* cd = AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.0f, 1.0f));


			const float pi = 3.141592f;
			float degree = pi / 8.0f;

			GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
			GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.5f, 1.0f));
			//player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));

			MeshRenderer* mr = AddComponent<MeshRenderer>();
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

			Animator* at = AddComponent<Animator>();
			at->Create(L"MoveDown", MoveDownTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 48.0f), 6);
			at->Create(L"MoveUp", MoveUpTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 48.0f), 6);
			at->Create(L"MoveRight", MoveRightTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);
			at->Create(L"MoveLeft", MoveLeftTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);

			std::shared_ptr<Texture> StandLeftTex
				= Resources::Load<Texture>(L"StandLeftTex", L"..\\Resources\\Texture\\Player\\Stand\\StandLeft.png");

			std::shared_ptr<Texture> StandRightTex
				= Resources::Load<Texture>(L"StandRightTex", L"..\\Resources\\Texture\\Player\\Stand\\StandRight.png");

			std::shared_ptr<Texture> StandDownTex
				= Resources::Load<Texture>(L"StandDownTex", L"..\\Resources\\Texture\\Player\\Stand\\StandDown.png");

			std::shared_ptr<Texture> StandUpTex
				= Resources::Load<Texture>(L"StandUpTex", L"..\\Resources\\Texture\\Player\\Stand\\StandUp.png");

			at->Create(L"StandRight", StandRightTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);
			at->Create(L"StandLeft", StandLeftTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);
			at->Create(L"StandDown", StandDownTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 48.0f), 6);
			at->Create(L"StandUp", StandUpTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 48.0f), 6);
		}
	
	}

	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}

}