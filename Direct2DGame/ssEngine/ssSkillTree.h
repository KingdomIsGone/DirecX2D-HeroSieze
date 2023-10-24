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
		wchar_t* IntToWchar(int num);

		void SetOnOff(bool is) { mOn = is; }
		bool GetOnOff() { return mOn; }
		void SetDim(class Dim* dim) { mDim = dim; }
		

	private:
		Transform* mTransform;
		Vector3 mPos;
		bool mOn;

		int mSkillPoint;

		class MeshRenderer* mRenderer;
		class Dim* mDim;
		class SkillPointText* mText;
	};
}