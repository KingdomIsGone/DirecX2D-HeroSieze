#pragma once
#include "ssGameObject.h"

namespace ss
{
	class CloneAssault : public GameObject
	{
	public:
		CloneAssault(e4Direction dir);
		~CloneAssault();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindCB(float Radd, float Gadd, float Badd, float A);
		void SetStart();

		class CloneScript* GetCloneScript() { return mScript; }
		

	private:
		Transform* mTransform;
		Vector3 mPos;
		Vector3 mOffset;
		e4Direction mDir;
		class Animator* mAnimator;
		
		class CloneScript* mScript;
	};
}