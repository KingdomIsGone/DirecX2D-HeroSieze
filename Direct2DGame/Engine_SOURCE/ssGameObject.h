#pragma once
#include "ssEntity.h"
#include "ssComponent.h"
#include "ssScript.h"

namespace ss
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Dead,
			Active,
			Paused,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* other) {};
		virtual void OnCollisionStay(Collider2D* other) {};
		virtual void OnCollisionExit(Collider2D* other) {};

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		template <typename T>
		const std::vector<T*> GetComponents()
		{
			std::vector<T*> comps;

			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					comps.push_back(component);
			}

			return comps;
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			
			Component* buff
				= dynamic_cast<Component*>(comp);
			Script* script
				= dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);
			
			comp->SetOwner(this);
			comp->Initialize();

			return comp;
		}

		void SetState(eState state) { mState = state; }
		eState GetState() { return mState; }

		std::vector<Component*> GetComponentVector() { return mComponents; }

		//custom
		struct OtherGameObject
		{
			GameObject* gameObject;
			eLayerType layerType;
		};

		void AddOtherGameObject(GameObject* obj, eLayerType type)
		{
			OtherGameObject* otherGameobject = new OtherGameObject();
			otherGameobject->gameObject = obj;
			otherGameobject->layerType = type;

			if (obj->GetParent() == nullptr)
				mGameObjects.push_back(otherGameobject);
			else
			{
				GameObject* parent = obj->GetParent();
				GameObject* lastChild = parent;
				while (parent != nullptr)
				{
					lastChild = parent;
					parent = parent->GetParent();
				}
				lastChild->PushBackOtherGameObject(otherGameobject);
			}
		}
		std::vector<OtherGameObject*> GetOtherGameObjects() { return mGameObjects; }

		float GetChangeHpValue() { return mChaingeHpValue; }
		void SetChangeHpValue(float value) { mChaingeHpValue = value; }
		
		GameObject* GetParent() { return mParent; }
		void SetParent(GameObject* obj) { mParent = obj; }
		void PushBackOtherGameObject(OtherGameObject* otherObj) { mGameObjects.push_back(otherObj); }

		void SetIsPlayerLayer(bool is) { mbPlayerLayer = is; }
		bool GetIsPlayerLayer() { return mbPlayerLayer; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;
		std::vector<OtherGameObject*> mGameObjects;

		//CUSTOM
		float mChaingeHpValue;
		bool mIsChild;
		GameObject* mParent;
		bool mbPlayerLayer;
	};
}
