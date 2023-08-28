#pragma once
class ImmuneText
{
};

#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ImmuneText : public GameObject
	{
	public:
		ImmuneText();
		~ImmuneText();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void setPos(Vector3 pos) { mPos = pos; }

		void SetTextMater();
		void SetBlank();
		void SetText() { mbText = true; }

	private:
		Transform* mTransform;
		Vector3 mPos;

		bool mbText;
		float mDelayTime;

		class Animator* mAnimator;
		class MeshRenderer* mRenderer;
	};
}