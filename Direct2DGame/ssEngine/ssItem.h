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

		enum class eItemState
		{
			Inventory,
			Field,
			Monster,
		};

		void SetMaterialName(std::wstring name);
		std::wstring GetMaterName() { return mMaterName; }

		eItemGrade GetItemGrade() { return mGrade; }
		void SetItemGrade(eItemGrade grade) { mGrade = grade; }
		eItemKind GetItemKind() { return mKind; }
		void SetItemKind(eItemKind kind) { mKind = kind; }
		eItemState GetItemState() { return mState; }
		void SetItemState(eItemState state) { mState = state; }

		bool GetImageOn() { return mImageOn; }
		void SetImageOn(bool is) { mImageOn = is; }

		void SetItemName(const wchar_t name[]) 
		{
			for (int i = 0; i < 20; i++)
			{
				mItemName[i] = name[i];
			}
		}
		wchar_t* GetItemName()
		{
			wchar_t* name = new wchar_t[20];
			for (int i = 0; i < 20; i++)
			{
				name[i] = mItemName[i];
			}
			
			return name;
		}
		void SetItemText(const wchar_t text[]) 
		{
			for (int i = 0; i < 20; i++)
			{
				mItemText[i] = text[i];
			}
		}
		wchar_t* GetItemText()
		{
			wchar_t* text = new wchar_t[20];
			for (int i = 0; i < 20; i++)
			{
				text[i] = mItemText[i];
			}

			return text;
		}


	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;
		wchar_t mItemName[20];
		wchar_t mItemText[20];

		class MeshRenderer* mRenderer;

		eItemState mState;
		eItemKind mKind;
		eItemGrade mGrade;

		bool mImageOn;
	};
}
