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

		void SetItemIn(bool is) { mItemIn = is; }
		void SetMaterName(std::wstring name) { mMaterName = name; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;

		bool mItemIn;
	};
}