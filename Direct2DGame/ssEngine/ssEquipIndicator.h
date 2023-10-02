#pragma once
#include "ssGameObject.h"

namespace ss
{
	class EquipIndicator : public GameObject
	{
	public:
		EquipIndicator(GameObject* parent);
		~EquipIndicator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetBlank();
		void SetSelected(bool is) { mSelected = is; }
		bool GetSelected() { return mSelected; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		class MeshRenderer* mRenderer;

		bool mSelected;
	};
}