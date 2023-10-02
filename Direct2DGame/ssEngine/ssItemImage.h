#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ItemImage : public GameObject
	{
	public:
		ItemImage(GameObject* parent);
		~ItemImage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetBlank();

		void SetOnList(bool is) { mOnList = is; }
		void SetOnEquip(bool is) { mOnEquip = is; }
		void SetMaterName(std::wstring name) { mMaterName = name; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;

		bool mOnList;
		bool mOnEquip;
	};
}