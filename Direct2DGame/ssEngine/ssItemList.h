#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ItemList : public GameObject
	{
	public:
		ItemList(GameObject* obj);
		~ItemList();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMaterialName(std::wstring name);
		void SetMater();
		void SetBlank();

		bool GetItemIn() { return mItemIn; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;
		class ItemBackground* mItemBack;

		bool mItemIn;
	};
}