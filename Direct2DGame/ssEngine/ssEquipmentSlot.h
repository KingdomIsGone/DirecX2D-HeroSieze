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

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;
	};
}