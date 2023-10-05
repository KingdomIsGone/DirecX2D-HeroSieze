#pragma once
#include "ssGameObject.h"

namespace ss
{
	class layer1 : public GameObject
	{
	public:
		layer1();
		~layer1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Transform* mTransform;
		Vector3 mPos;
	};
}