#pragma once
class SkillSelectBox
{
};

#pragma once
#include "ssGameObject.h"

namespace ss
{
	class SkillSelectBox : public GameObject
	{
	public:
		SkillSelectBox(GameObject* obj);
		~SkillSelectBox();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		struct SkillInfo
		{
			UINT ID = -1;
			std::wstring Mater;
			float CoolTime;
		};

		void ImageSort();

		void SetSkillCountPlus() { mLearnedSkillCount++; }
		void SetOnOff(bool is) { mOn = is; }
		bool GetOnOff() { return mOn; }
		void SetSkillSlot(class SkillSlot* slot) { mSkillSlot.push_back(slot); }

		void SlotClickCheck();
		void SelectClickCheck();

	private:
		Transform* mTransform;
		Vector3 mPos;
		bool mOn;

		class MeshRenderer* mRenderer;
		class SkillSelectImage* mSelectImage[6];
		std::vector<SkillSlot*> mSkillSlot;

		SkillInfo mSkills[6];
		static UINT mLearnedSkillCount;
		UINT mSelectSlotNum;

	};
}