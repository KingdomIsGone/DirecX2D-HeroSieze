#pragma once
#include "ssGameObject.h"

namespace ss
{
	class TorchBig : public GameObject
	{
	public:
		TorchBig();
		~TorchBig();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Transform* mTransform;
		Vector3 mPos;

	};
}