#pragma once
#include "ssGameObject.h"

namespace ss
{
	class SkillSlot : public GameObject
	{
	public:
		SkillSlot();
		~SkillSlot();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void CoolTimeStart();
		void BindCB();
		float GetCoolPer() { return mCoolPercent; }
		
		void SetMater(std::wstring name);
		void SetSlotNum(UINT num) { mSlotNum = num; }
		void SetCoolSpeed(float speed) { mCoolSpeed = speed; }

		bool GetReady();

	private:
		Transform* mTransform;
		Vector3 mPos;
		class MeshRenderer* mMeshRenderer;

		float mCoolPercent;
		float mCoolSpeed;
		bool mOnCool;
		std::wstring mMaterName;
		UINT mSlotNum;
	};
}