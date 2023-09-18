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

		static Vector3 GetPos() { return mPos; }
		Vector3 GetProjPos() { return mprojPos; }

	private:
		Transform* mTransform;
		static Vector3 mPos;
		static Vector3 mprojPos;
		Vector3 mOffset;

		class MeshRenderer* mMr;
	};
}
