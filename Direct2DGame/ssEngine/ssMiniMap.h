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

		void SetMiniMap(std::wstring name, float Width, float Height, float WidthScale, float HeightScale);
		void SetRatioLength(float width, float height) { mRatioWidth = width; mRatioHeight = height; }

		void CalUVPos();
		void BindCB();
		void SetSize();

	private:
		Transform* mTransform;
		std::wstring mTextureName;

		Vector3 mPos;
		Vector3 mPlayerPos;
		Vector2 mUVPos;
		Vector2 mBasePos;

		float mXmoveAmount;
		float mYmoveAmount;
		bool OnceIgnore;

		class MeshRenderer* mMeshRenderer;

		float mRatioWidth;
		float mRatioHeight;

		float mWidth;
		float mHeight;

		GameObject* mMapDot;

	};
}