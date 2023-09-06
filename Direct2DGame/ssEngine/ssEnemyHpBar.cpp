#include "ssEnemyHpBar.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

namespace ss
{
	EnemyHpBar::EnemyHpBar()
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
