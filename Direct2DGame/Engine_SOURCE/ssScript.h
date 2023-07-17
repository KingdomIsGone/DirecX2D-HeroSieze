#pragma once
#include "ssComponent.h"
#include "ssCollider2D.h"


namespace ss
{
	class Script : public Component
	{
	public:
		Script();
		~Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) {};
		virtual void OnCollisionStay(Collider2D* other) {};
		virtual void OnCollisionExit(Collider2D* other) {};

	private:

	};
}
