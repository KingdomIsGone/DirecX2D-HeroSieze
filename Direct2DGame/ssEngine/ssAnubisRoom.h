#pragma once
//#include "ssScene.h"
#include "..\Engine_SOURCE\ssScene.h"

namespace ss
{
	class AnubisRoom : public Scene
	{
	public:
		AnubisRoom();
		virtual ~AnubisRoom();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		class Cursor* cursor;
		class AudioSource* mAs;

		class Anubis* mAnubis;
		class BossHpBar* mBossHpBar;
		class BossHpFill* mBossHpFill;
		class BossName* mBossName;

		class Camera* mMainCamera;
		class Camera* mPlayerCamera;
		class Camera* mUICamera;
		class Camera* mCursorCamera;
		class Camera* mInventoryCamera;
		class Camera* mMonUICamera;

		bool mPortalOnce;
		bool mSoundOnce;
	};
}
