#include "ssCursor.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"

namespace ss
{
	Cursor::Cursor()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Cursor1Mater"));
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		tr->SetPosition(Vector3::Zero);
	}
	Cursor::~Cursor()
	{
	}
	void Cursor::Initialize()
	{
		GameObject::Initialize();
	}
	void Cursor::Update()
	{
		GameObject::Update();
	}
	void Cursor::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Cursor::Render()
	{
		GameObject::Render();
	}
}
