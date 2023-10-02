#include "TestObject.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssCursor.h"
#include "ssPlayerScript.h"
#include "ssInput.h"

namespace ss
{
	TestObject::TestObject(GameObject* parent)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();
		Vector3 pos = mTransform->GetPosition();
		pos.z -= 0.13f;
		mTransform->SetPosition(pos);
		mTransform->SetScale(Vector3(1.f, 1.0f, 1.f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"TestAlphaMater"));

	}

	TestObject::~TestObject()
	{
	}

	void TestObject::Initialize()
	{
		GameObject::Initialize();
	}
	void TestObject::Update()
	{
		GameObject::Update();

		

	}
	void TestObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void TestObject::Render()
	{
		GameObject::Render();
	}

	
}
