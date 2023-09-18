#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ItemList : public GameObject
	{
	public:
		ItemList(GameObject* parent);
		~ItemList();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMaterialName(std::wstring name);
		void SetMater();
		void SetBlank();

		bool GetItemIn() { return mItemIn; }
		void SetItemIn(bool is) { mItemIn = is; }

		void SetItem(class Item* item) { mItem = item; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;
		class ItemBackground* mItemBack;
		class ItemImage* mItemImage;
		class Item* mItem;

		bool mItemIn;
	};
}