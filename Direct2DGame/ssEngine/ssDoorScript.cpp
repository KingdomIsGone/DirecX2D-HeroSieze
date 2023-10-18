#include "ssDoorScript.h"
#include "ssGameObject.h"
#include "ssSceneManager.h"

namespace ss
{
	DoorScript::DoorScript()
	{
	}
	DoorScript::~DoorScript()
	{
	}
	void DoorScript::Initialize()
	{
	}
	void DoorScript::Update()
	{

	}
	void DoorScript::OnCollisionEnter(Collider2D* other)
	{
		if (other->GetCollideType() == eCollideType::Player)
		{
			std::wstring name = GetOwner()->GetName();
			if(name == L"DesertDoor")
				SceneManager::LoadScene(L"AnubisRoom");
			else if (name == L"TownDoor")
				SceneManager::LoadScene(L"DesertMap");
			else if (name == L"ForestDoor")
				SceneManager::LoadScene(L"ValkyrieScene");
			else if (name == L"Portal")
				SceneManager::LoadScene(L"ForestScene");

		}

	}
	void DoorScript::OnCollisionStay(Collider2D* other)
	{

	}
	void DoorScript::OnCollisionExit(Collider2D* other)
	{
	}
}
