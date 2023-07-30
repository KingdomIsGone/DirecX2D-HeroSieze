#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Cursor : public GameObject
	{
	public:
		Cursor();
		~Cursor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		Vector3 GetPos() { return mPos; }

	private:
		Transform* mTransform;
		static Vector3 mPos;
		Vector3 mOffset;
	};
}
