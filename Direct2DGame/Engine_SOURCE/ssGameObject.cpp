#include "ssGameObject.h"
#include "ssRenderer.h"
#include "ssGraphicDevice_Dx11.h"
#include "ssTransform.h"

namespace ss
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			delete script;
			script = nullptr;
		}

		for (OtherGameObject* object : mGameObjects)
		{
			if (object == nullptr)
				continue;

			delete object;
			object = nullptr;
		}
	}

	void GameObject::Initialize()
	{

	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}

		for (Script* script : mScripts)
		{
			script->Update();
		}

		for (OtherGameObject* object : mGameObjects)
		{
			object->gameObject->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}

		for (Script* script : mScripts)
		{
			script->LateUpdate();
		}

		for (OtherGameObject* object : mGameObjects)
		{
			object->gameObject->LateUpdate();
		}
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			comp->Render();
		}
		//������۷� ��ġ���� ũ������, ����, ������Ʈ ������Ѵ�.

		for (Script* script : mScripts)
		{
			script->Render();
		}

		for (OtherGameObject* object : mGameObjects)
		{
			object->gameObject->Render();
		}
	}
}
