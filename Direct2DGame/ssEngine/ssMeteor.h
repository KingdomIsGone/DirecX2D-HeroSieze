#pragma once
#include "ssGameObject.h"

namespace ss
{
	class Meteor : public GameObject
	{
	public:
		Meteor();
		~Meteor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Transform* mTransform;
		Vector3 mPos;

		float mDamage;
		float mDelayTime;
		UINT mStage;
		float mTargetY;

		class MeteorScript* mMScript;
		class Animator* mAnimator;
		class AudioSource* mAs;
		bool mAudioOnce;
	};
}