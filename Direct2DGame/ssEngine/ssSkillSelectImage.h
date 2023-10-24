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

		std::wstring GetMaterName() { return mMaterName; }
		void SetID(eSkillID id) { mID = id; }
		eSkillID GetID() { return mID; }
		void SetCoolTime(float time) { mCoolTime = time; }
		float GetCoolTime() { return mCoolTime; }
		void SetSkillID(eSkillID id) { mID = id; }
		eSkillID GetSkillID() { return mID; }

		void SetTex(std::shared_ptr<Texture> tex) { mTex = tex; }
		std::shared_ptr<Texture> GetTex() { return mTex; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		std::wstring mMaterName;
		eSkillID mID;
		float mCoolTime;

		class MeshRenderer* mRenderer;
		std::shared_ptr<Texture> mTex;
		class SkillSelectBox* mBox;

		bool mIn;
		bool mOn;
			
	};
}