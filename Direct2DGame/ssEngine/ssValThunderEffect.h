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
		void SetClone(class CloneAssault* clone) { mClone = clone; mIsClone = true; SetName(L"cloneTh"); }
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

		bool mIsClone;
		class Valkyrie* mValk;
		class CloneAssault* mClone;
		class Animator* mAnimator;

		class ThunderPiece* mLeftPiece;
		class ThunderPiece* mMLeftPiece;
		class ThunderPiece* mMiddlePiece;
		class ThunderPiece* mMRightPiece;
		class ThunderPiece* mRightPiece;

	};
}