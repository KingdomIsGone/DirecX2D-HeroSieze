#pragma once
#include "ssGameObject.h"

namespace ss
{
	class EquipmentSlot : public GameObject
	{
	public:
		EquipmentSlot();
		~EquipmentSlot();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMaterialName(std::wstring name);
		void SetMater();
		void SetBlank();

		void SetItemBack(class ItemBackground* back) { mBackGround = back; }
		ItemBackground* GetItemBack() { return mBackGround; }
		void SetItemImage(class ItemImage* image) { mItemImage = image; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;
		class ItemBackground* mBackGround;
		class ItemImage* mItemImage;
	};
}