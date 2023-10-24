#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Number : public GameObject
	{
	public:
		Number(GameObject* obj);
		~Number();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetOnOff(bool is) { mOn = is; }
		bool GetOnOff() { return mOn; }

		void SetNum(UINT num) { mNum = num; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		bool mOn;

		UINT mNum;

		class MeshRenderer* mRenderer;

	};
}