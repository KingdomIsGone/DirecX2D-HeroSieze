#pragma once
class LvUpEffector
{
};

#pragma once
#include "ssGameObject.h"

namespace ss
{
	class LvUpEffector : public GameObject
	{
	public:
		LvUpEffector();
		~LvUpEffector();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Play();
		void PlayEffect();

		enum class eState
		{
			Waiting,
			Play,
			Play2,
		};

	private:
		Transform* mTransform;
		Vector3 mPos;
		Vector2 mOffset;

		class Animator* mAnimator;
		class AudioSource* mAs;
		eState mState;
		bool mOn;
	};
}