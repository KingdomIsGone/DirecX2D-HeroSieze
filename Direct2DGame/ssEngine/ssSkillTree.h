#pragma once
#include "ssGameObject.h"

namespace ss
{
	class SkillTree : public GameObject
	{
	public:
		SkillTree(GameObject* obj);
		~SkillTree();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetOnOffCheck();
		void SetClickCheck();
		void LearnCheck();
		void Renew();

		wchar_t* IntToWchar(int num);

		void AddSkillPoint() { mSkillPoint++; }
		void SetOnOff(bool is) { mOn = is; }
		bool GetOnOff() { return mOn; }
		void SetDim(class Dim* dim) { mDim = dim; }
		
		std::bitset<5> GetSkLevelBitSet();

	private:
		Transform* mTransform;
		Vector3 mPos;
		bool mOn;

		static UINT mSkillPoint;

		class MeshRenderer* mRenderer;
		class Dim* mDim;
		class SkillPointText* mText;

		class SkillIcon* mSkillIcon[5];
		class SkillIcon* mInvalidIcon[5];
		class SkillIcon* mLine[6];
		class SkillLevel* mLevel[10];
		class Number* mLevelNumber[11];
		
		static UINT mFireWallLevel;
		static UINT mFireAuraLevel;
		static UINT mHydraLevel;
		static UINT mMeteorLevel;
		static UINT mTelePortLevel;

	};
}