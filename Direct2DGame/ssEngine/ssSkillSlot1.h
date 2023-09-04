#pragma once
#include "ssGameObject.h"

namespace ss
{
	class SkillSlot1 : public GameObject
	{
	public:
		SkillSlot1();
		~SkillSlot1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


	private:
		Transform* mTransform;
		Vector3 mPos;
	};
}