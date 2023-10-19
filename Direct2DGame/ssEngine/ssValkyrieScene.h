#pragma once
#include "..\Engine_SOURCE\ssScene.h"

namespace ss
{
	class ValkyrieScene : public Scene
	{
	public:
		ValkyrieScene();
		virtual ~ValkyrieScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void CameraWalkUp();

	private:
		class Camera* mMainCamera;
		class Camera* mPlayerCamera;
		class Camera* mUICamera;
		class Camera* mCursorCamera;
		class Camera* mInventoryCamera;
		class Camera* mMonUICamera;


		class BossHpBar* mBossHpBar;
		class BossHpFill* mBossHpFill;
		class Valkyrie* mValkyrie;
		class ValAwaker* mValAwaker;
		class BossName* mBossName;
		class PlayerScript* mPlayerScript;
		class AudioSource* mAs;

		bool mSoundOnce;
		bool mbFont;

		GameObject* mObjMainCamera;
		GameObject* mObjPlayerCamera;
		class PlayerCameraScript* mPlayerCameraScirpt;
		float mCameraDistance;
		UINT mCWStage;
		Vector3 mPlayerInitialPos;
		Vector3 mCameraInitialPos;
		Vector3 mPlayerInitialCameraPos;

	};
}
