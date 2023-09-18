#pragma once
#include "ssGameObject.h"
#include "ssCollider2D.h"

namespace ss
{
	class Item : public GameObject
	{
	public:
		Item();
		~Item();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


		enum class eItemGrade
		{
			Normal,
			Magic,
			Legend,
		};
		enum class eKind
		{
			Weapon,
			Armor,
			Shield,
			Helmet,
			Belt,
			Shoes,
		};
		enum class eItemState
		{
			Inventory,
			Field,
		};

		void SetMaterialName(std::wstring name);
		std::wstring GetMaterName() { return mMaterName; }

		eItemGrade GetItemGrade() { return mGrade; }
		void SetItemGrade(eItemGrade grade) { mGrade = grade; }
		eKind GetItemKind() { return mKind; }
		void SetItemKind(eKind kind) { mKind = kind; }
		eItemState GetItemState() { return mState; }
		void SetItemState(eItemState state) { mState = state; }

		bool GetImageOn() { return mImageOn; }
		void SetImageOn(bool is) { mImageOn = is; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;

		eItemState mState;
		eKind mKind;
		eItemGrade mGrade;

		bool mImageOn;
	};
}
