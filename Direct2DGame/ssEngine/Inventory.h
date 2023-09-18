#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Inventory : public GameObject
	{
	public:
		Inventory(GameObject* obj);
		~Inventory();

		enum class eKind
		{
			Weapon,
			Armor,
			Shield,
			Helmet,
			Belt,
			Shoes,
			End,
		};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void TurnOnOff(bool is) { mOn = is; }
		bool GetOnOff() { return mOn; }

		void SetLight(class Light* light) { mLight = light; }
		void PushBackEquipSlot(class EquipmentSlot* slot) { mEquipSlots.push_back(slot); }
		void OnOffCheck();
		void CusorOnEquipCheck();
		void ActivateItemList(UINT num);

		static void PushbackItem(class Item* item);

	private:
		Transform* mTransform;
		Vector3 mPos;
		bool mOn;

		class MeshRenderer* mRenderer;
		class Light* mLight;

		std::vector<EquipmentSlot*> mEquipSlots;

		class ItemList* mList1;
		class ItemList* mList2;
		class ItemList* mList3;
		std::vector<ItemList*> mItemLists;

		static std::vector<class Item*> mWeapons;
		static std::vector<Item*> mArmors;
		static std::vector<Item*> mShields;
		static std::vector<Item*> mHelmets;
		static std::vector<Item*> mBelts;
		static std::vector<Item*> mShoes;

		std::bitset<(UINT)eKind::End> mItemKindMask;
	};
}