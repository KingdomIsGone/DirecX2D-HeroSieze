#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ChargedBolt : public GameObject
	{
	public:
		ChargedBolt(bool isVertical);
		~ChargedBolt();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetForInstance(bool is) { mForInstance = is; }
		static float GetDamage() { return mDamage; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		float mSpeed;

		float mDeleteTime;
		float mWaitTime;
		bool mForInstance;

		bool mbIsVertical;

		class Collider2D* mCollider;

		static float mDamage;
	};
}
