#pragma once
#include "ssGameObject.h"

namespace ss
{
	class SkillLevel : public GameObject
	{
	public:
		SkillLevel(GameObject* obj);
		~SkillLevel();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetOnOff(bool is) { mOn = is; }
		bool GetOnOff() { return mOn; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		bool mOn;

		class MeshRenderer* mRenderer;

	};
}