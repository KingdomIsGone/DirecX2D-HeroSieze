#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ItemBackground : public GameObject
	{
	public:
		enum class eGrade
		{
			Normal,
			Magic,
			Legend,
		};	
		ItemBackground(GameObject* parent);
		~ItemBackground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMaterNormal();
		void SetMaterMagic();
		void SetMaterLegend();
		void SetBlank();

		void SetOnList(bool is) { mOnList = is; }
		void SetOnEquip(bool is) { mOnEquip = is; }
		void SetItemGrade(UINT grade) { mGrade = (eGrade)grade; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;
		
		bool mOnList;
		bool mOnEquip;
		eGrade mGrade;
	};
}