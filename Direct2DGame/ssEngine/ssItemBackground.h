#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ItemBackground : public GameObject
	{
	public:
		ItemBackground(GameObject* obj);
		~ItemBackground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMaterNormal();
		void SetMaterMagic();
		void SetMaterLegend();
		void SetBlank();

		void SetItemIn(bool is) { mItemIn = is; }

		enum class eGrade
		{
			Normal,
			Magic,
			Legend,
		};

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;

		bool mItemIn;
		eGrade mGrade;
	};
}