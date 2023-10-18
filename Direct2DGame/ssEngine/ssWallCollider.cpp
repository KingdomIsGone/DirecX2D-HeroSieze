#include "ssWallCollider.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"

namespace ss
{
	WallCollider::WallCollider()
	{
		mTransform = GetComponent<Transform>();

		mCol = AddComponent<Collider2D>();
		mCol->SetCollideType(eCollideType::Wall);
	}
	WallCollider::~WallCollider()
	{
	}
	void WallCollider::Initialize()
	{
		GameObject::Initialize();
	}
	void WallCollider::Update()
	{
		GameObject::Update();
	}
	void WallCollider::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void WallCollider::Render()
	{
		GameObject::Render();
	}
}
