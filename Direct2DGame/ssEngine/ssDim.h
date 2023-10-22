#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Dim : public GameObject
	{
	public:
		Dim();
		~Dim();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetOnOff(bool is);
		

	private:
		class MeshRenderer* mMr;
		class Transform* mTransform;

		bool mRenderOn;

	};
}
