#pragma once
//#include "ssScene.h"
#include "..\Engine_SOURCE\ssScene.h"

namespace ss
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;


	private:
		class Cursor* mCursor;
		class Animator* mTornadoAni;
		class MeshRenderer* mBtnMr;
		class StartBtn* mStBtn;
		class AudioSource* mAs;

		UINT mTornadoNum;
	};
}
