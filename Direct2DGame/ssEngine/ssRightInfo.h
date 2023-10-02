#pragma once
#include "ssGameObject.h"

namespace ss
{
	class RightInfo : public GameObject
	{
	public:
		RightInfo(GameObject* parent);
		~RightInfo();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetBlank();
		void SetItem(class Item* item) { mItem = item; }
		void TurnOnOff(bool is) { mOn = is; }
		void SetItemBack(class ItemBackground* back) { mItemBack = back; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		class MeshRenderer* mRenderer;
		class Item* mItem;
		class ItemBackground* mItemBack;

		bool mOn;
	};
}