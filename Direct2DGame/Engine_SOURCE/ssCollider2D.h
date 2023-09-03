#pragma once
#include "ssComponent.h"
#include "ssTransform.h"

namespace ss
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		void SetType(eColliderType type) { mType = type; }
		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }
		Vector2 GetCenter() { return mCenter; }
		UINT GetColliderID() { return mColliderID; }

		//Custom
		static bool GetIsCollide() { return mIsCollide; }
		void SetColIsPlayer(bool is) { mColIsPlayer = is; }
		bool GetColIsPlayer() { return mColIsPlayer; }

		void SetCollideType(eCollideType type) { mCollideType = type; }
		eCollideType GetCollideType() { return mCollideType; }

		Collider2D* GetPlayerCol() { return mPlayerCol; }
		void SetPlayerCol(Collider2D* col) { mPlayerCol = col; }

		void SetLeftCol(bool is) { mLeftCol = is; }
		void SetRightCol(bool is) { mRightCol = is; }
		void SetTopCol(bool is) { mTopCol = is; }
		void SetBottomCol(bool is) { mBottomCol = is; }
		bool GetLeftCol() { return mLeftCol; }
		bool GetRightCol() { return mRightCol; }
		bool GetTopCol() { return mTopCol; }
		bool GetBottomCol() { return mBottomCol; }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		eCollideType mCollideType;
		Transform* mTransform;
		
		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;

		static bool mIsCollide;
		bool mColIsPlayer;
		Collider2D* mPlayerCol;

		bool mRightCol;
		bool mLeftCol;
		bool mTopCol;
		bool mBottomCol;
	};
}
