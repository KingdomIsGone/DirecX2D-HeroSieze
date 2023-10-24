#pragma once
#include "ssGameObject.h"

namespace ss
{
	class SkillIcon : public GameObject
	{
	public:
		SkillIcon(GameObject* obj);
		~SkillIcon();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetOnOff(bool is) { mOn = is; }
		bool GetOnOff() { return mOn; }

		void SetAble(bool is) { mAble = is; }
		bool GetAble() { return mAble; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		bool mOn;
		bool mAble;

		int mPoint;

		class MeshRenderer* mRenderer;
		
	};
}