#pragma once
#include "ssGameObject.h"

namespace ss
{
	class FireWall : public GameObject
	{
	public:
		FireWall(Vector3 cursorPos);
		~FireWall();

		enum class eStage
		{
			firstOne,
			delay1,
			firstTwo,
			delay2,
			secondTwo,
			delay3,
			ThirdTwo,
			continueTime,
		};

		enum eDegreeCase
		{
			UpDown,
			RightLeft,
			Ohter,
		};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void FirstOne();
		void Delay1();
		void FirstTwo();
		void Delay2();
		void SecondTwo();
		void Delay3();
		void ThirdTwo();
		void ContinueTime();

	private:
		Transform* mTransform;
		Vector3 mPos;
		Vector3 mCursorPos;
		Vector3 mWallPos[7];

		float mDelayTime;
		float mInclination;
		float mDistance;
		float mDegree;

		class FireWallPiece* mWalls[7];

		eStage mStage;
		eDegreeCase mCase;
	};
}