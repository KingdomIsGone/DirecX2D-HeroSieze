#pragma once
#include "ssGameObject.h"

namespace ss
{
	class TestObject : public GameObject
	{
	public:
		TestObject(GameObject* parent);
		~TestObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;

	};
}