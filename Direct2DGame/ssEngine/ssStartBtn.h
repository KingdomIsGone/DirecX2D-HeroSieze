#pragma once
#include "ssGameObject.h"

namespace ss
{
	class StartBtn : public GameObject
	{
	public:
		StartBtn();
		~StartBtn();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetBtn1();
		void SetBtn2();
		void SetClicked(bool is) { mClicked = is; }

	private:
		Vector3 mPos;

		class MeshRenderer* mRenderer;

		bool mClicked;

	};
}