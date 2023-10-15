#include "ssValAwaker.h"
#include "ssCollider2D.h"
#include "ssAwakerScript.h"

namespace ss
{
	ValAwaker::ValAwaker()
	{
		mCollider = AddComponent<Collider2D>();
		mCollider->SetCollideType(eCollideType::Item);
		mScript = AddComponent<AwakerScript>();
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(3.f, 0.3f, 1.f);
	}
	ValAwaker::~ValAwaker()
	{
	}
	void ValAwaker::Initialize()
	{
		GameObject::Initialize();
	}
	void ValAwaker::Update()
	{
		GameObject::Update();
	}
	void ValAwaker::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void ValAwaker::Render()
	{
		GameObject::Render();
	}
}
