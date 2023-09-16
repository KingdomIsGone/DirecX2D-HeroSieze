#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Inventory : public GameObject
	{
	public:
		Inventory();
		~Inventory();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void TurnOnOff(bool is) { mOn = is; }
		bool GetOnOff() { return mOn; }
		void SetLight(class Light* light) { mLight = light; }
		void PushBackEquipSlot(class EquipmentSlot* slot) { mEquipSlots.push_back(slot); }
		void OnOffCheck();

	private:
		Transform* mTransform;
		Vector3 mPos;
		bool mOn;

		class MeshRenderer* mRenderer;
		class Light* mLight;

		std::vector<EquipmentSlot*> mEquipSlots;
	};
}