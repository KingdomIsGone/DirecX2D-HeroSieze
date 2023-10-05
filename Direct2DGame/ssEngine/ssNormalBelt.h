#pragma once
#include "ssItem.h"

namespace ss
{
	class NormalBelt : public Item
	{
	public:
		NormalBelt();
		~NormalBelt();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		Transform* mTransform;
		Vector3 mPos;
		class MeshRenderer* mRenderer;
		class Collider2D* mCollider;

		eItemState mState;
	};
}