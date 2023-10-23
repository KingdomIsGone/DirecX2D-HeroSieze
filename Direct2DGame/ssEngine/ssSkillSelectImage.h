#pragma once
class SkillSelectImage
{
};

#pragma once
#include "ssGameObject.h"

namespace ss
{
	class SkillSelectImage : public GameObject
	{
	public:
		SkillSelectImage(GameObject* parent);
		~SkillSelectImage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMaterName(std::wstring name) { mMaterName = name; }
		void SetMater();

		void SetInSkill(bool is) { mIn = is; }
		bool GetInSkill() { return mIn; }
		void SetOnOff(bool is) { mOn = is; }
		void SetBox(class SkillSelectBox* box) { mBox = box; }

	private:
		Transform* mTransform;
		Vector3 mPos;
		std::wstring mMaterName;

		class MeshRenderer* mRenderer;
		class SkillSelectBox* mBox;

		bool mIn;
		bool mOn;
			
	};
}