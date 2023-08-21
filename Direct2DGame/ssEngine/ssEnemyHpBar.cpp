#include "ssEnemyHpBar.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

namespace ss
{
	EnemyHpBar::EnemyHpBar()
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.2f, 1.2f, 1.0f));
		//mTransform->SetParent()
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"EnemyHpBarMater"));


	}
	EnemyHpBar::~EnemyHpBar()
	{
	}
	void EnemyHpBar::Initialize()
	{
	}
	void EnemyHpBar::Update()
	{
	}
	void EnemyHpBar::LateUpdate()
	{
	}
	void EnemyHpBar::Render()
	{
	}
}
