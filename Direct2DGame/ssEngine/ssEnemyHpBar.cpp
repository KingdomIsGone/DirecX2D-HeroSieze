#include "ssEnemyHpBar.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

namespace ss
{
	EnemyHpBar::EnemyHpBar()
		: mOffsetX(0.f)
		, mOffsetY(0.f)
	{
		SetName(L"enemyHpBar");
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(0.45f, 0.08f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		pos.y += 0.17f;
		pos.z -= 0.001f;
		mTransform->SetPosition(pos);
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"EnemyHpBarMater"));


	}
	EnemyHpBar::~EnemyHpBar()
	{
	}
	void EnemyHpBar::Initialize()
	{
		GameObject::Initialize();
	}
	void EnemyHpBar::Update()
	{
		GameObject::Update();

		Vector3 ownerPos = mOwnerTransform->GetPosition();
		ownerPos.x += mOffsetX;
		ownerPos.y += mOffsetY;
		ownerPos.z -= 0.05f;

		mTransform->SetPosition(ownerPos);
	}
	void EnemyHpBar::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void EnemyHpBar::Render()
	{
		GameObject::Render();
	}
}
