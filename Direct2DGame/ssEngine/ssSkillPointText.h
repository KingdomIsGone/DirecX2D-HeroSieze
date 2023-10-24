#pragma once
#include "ssGameObject.h"

namespace ss
{
	class SkillPointText : public GameObject
	{
	public:
		SkillPointText(GameObject* parent);
		~SkillPointText();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetOnOff(bool is) { mOn = is; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		bool mOn;

		class MeshRenderer* mRenderer;
	};
}