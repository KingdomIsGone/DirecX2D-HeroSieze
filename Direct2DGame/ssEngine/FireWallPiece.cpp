#include "FireWallPiece.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssTime.h"
#include "ssMeteorScript.h"
#include "ssFireWallPieceScript.h"

namespace ss
{
	FireWallPiece::FireWallPiece()
		: mDamage(500.0f)
	{
		SetName(L"FireWallPiece");
		mScript = AddComponent<FireWallPieceScript>();

		mTransform = GetComponent<Transform>();

		//콜라이더 세팅
		GetComponent<Transform>()->SetScale(1.3f, 1.3f, 1.0f);
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::Projectile);
		collider->SetSize(Vector2(0.15f, 0.26f));
		collider->SetCenter(Vector2(-0.00f, -0.05f));

		//렌더, 애니메이터 세팅
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

		mAnimator = AddComponent<Animator>();

		std::shared_ptr<Texture> FireWallTex
			= Resources::Load<Texture>(L"FireWallTex", L"..\\Resources\\Texture\\Skill\\FireWall\\FireWall26676.png");
		mAnimator->Create(L"FireWall", FireWallTex, Vector2(0.0f, 0.0f), Vector2(26.0f, 67.0f), 6);

		mTransform->SetScale(Vector3(1.4f, 1.4f, 1.0));

		mAnimator->PlayAnimation(L"FireWall", true);
	}
	FireWallPiece::~FireWallPiece()
	{
	}
	void FireWallPiece::Initialize()
	{
		GameObject::Initialize();
	}
	void FireWallPiece::Update()
	{
		GameObject::Update();
		mPos = mTransform->GetPosition();

	}
	void FireWallPiece::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void FireWallPiece::Render()
	{
		GameObject::Render();
	}
}