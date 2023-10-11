#pragma once
class ValThunderEffect
{
};

#pragma once
#include "ssGameObject.h"

namespace ss
{
	class ValThunderEffect : public GameObject
	{
	public:
		ValThunderEffect();
		~ValThunderEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetOffset(Vector3 offset) { mOffset = offset; }
		void SetPosition(Vector3 pos) { mPos = pos; }
		void SetValkyrie(class Valkyrie* valk) { mValk = valk; }
		void SetDead();
		void SetDown();
		void SetUp();
		void SetRight();
		void SetLeft();

	private:
		Transform* mTransform;
		Vector3 mPos;
		Vector3 mOffset;
		Vector3 mValkPos;

		class Valkyrie* mValk;
		class Animator* mAnimator;

		class ThunderPiece* mLeftPiece;
		class ThunderPiece* mMiddlePiece;
		class ThunderPiece* mRightPiece;

	};
}