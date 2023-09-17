#include "ssGameObject.h"
#include "ssRenderer.h"
#include "ssGraphicDevice_Dx11.h"
#include "ssTransform.h"
#include "ssCollider2D.h"
#include "..\\ssEngine\ssPlayerScript.h"

namespace ss
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mChaingeHpValue(0.f)
		, mParent(nullptr)
	{
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		Collider2D* col = GetComponent<Collider2D>();
		if (col != nullptr)
		{
			if (col->GetColIsPlayer())
			{
				col->GetPlayerCol()->OnCollisionExit(col);
			}
		}

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
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			comp->Render();
		}
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.

		for (Script* script : mScripts)
		{
			script->Render();
		}
	}
}
