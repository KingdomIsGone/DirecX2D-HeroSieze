#pragma once
#include "ssGameObject.h"

namespace ss
{
	class BossHpBar : public GameObject
	{
	public:
		BossHpBar();
		~BossHpBar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void setPos(Vector3 pos) { mPos = pos; }

		void SetHP();
		void SetBlank();

	private:
		Transform* mTransform;
		Vector3 mPos;

		class Animator* mAnimator;
		class MeshRenderer* mRenderer;
	};
}
