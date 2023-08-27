#pragma once
#include "ssGameObject.h"

namespace ss
{
	class P_HpSmallBar : public GameObject
	{
	public:
		P_HpSmallBar();
		~P_HpSmallBar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void setPos(Vector3 pos) { mPos = pos; }

	private:
		Transform* mTransform;
		Vector3 mPos;

	};
}
