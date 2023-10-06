#pragma once
#include "ssGameObject.h"

namespace ss
{
	class PlayerMpBarFill : public GameObject
	{
	public:
		PlayerMpBarFill();
		~PlayerMpBarFill();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void setPos(Vector3 pos) { mPos = pos; }

		void ChangeMP(float hp) { mMpChanged = true; mCurMP = hp; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		float mFullMpScale;
		float mCurMpScale;
		float mWidth;
		bool mMpChanged;
		float mCurMP;
		float mFullMP;
	};
}
