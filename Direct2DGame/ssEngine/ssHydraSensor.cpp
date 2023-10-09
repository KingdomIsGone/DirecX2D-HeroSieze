#include "ssHydraSensor.h"
#include "ssTexture.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssAnimator.h"
#include "ssCollider2D.h"
#include "ssTime.h"
#include "ssHydra.h"
#include "ssHydraScript.h"

namespace ss
{
	HydraSensor::HydraSensor()
		: mDamage(500.0f)
	{
		SetName(L"HydraSensor");
		mScript = AddComponent<HydraScript>();

		mTransform = GetComponent<Transform>();

		//콜라이더 세팅
		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetCollideType(eCollideType::Sensor);
		collider->SetSize(Vector2(5.f, 5.f));
		collider->SetCenter(Vector2(0.00f, -0.0f));



	}
	HydraSensor::~HydraSensor()
	{
	}
	void HydraSensor::Initialize()
	{
		GameObject::Initialize();
	}
	void HydraSensor::Update()
	{
		GameObject::Update();

		mTransform->SetPosition(mHydra->GetComponent<Transform>()->GetPosition());


	}
	void HydraSensor::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void HydraSensor::Render()
	{
		GameObject::Render();
	}
}