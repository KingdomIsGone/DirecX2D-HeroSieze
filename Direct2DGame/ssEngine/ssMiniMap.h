#pragma once
#include "ssGameObject.h"

namespace ss
{
	static class MiniMap : public GameObject
	{
	public:
		MiniMap();
		~MiniMap();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMiniMap(std::wstring name, float Width, float Height);
		void SetRatioLength(float width, float height) { mRatioWidth = width; mRatioHeight = height; }

		void CalUVPos();
		void BindCB();

	private:
		Transform* mTransform;
		std::wstring mTextureName;

		Vector3 mPos;
		Vector3 mPlayerPos;
		Vector2 mUVPos;
		Vector2 mPrevUVPos;

		float mXmoveAmount;
		float mYmoveAmount;

		class MeshRenderer* mMeshRenderer;

		float mRatioWidth;
		float mRatioHeight;

		GameObject* mMapDot;

	};
}