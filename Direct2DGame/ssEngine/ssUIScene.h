#pragma once
//#include "ssScene.h"
#include "..\Engine_SOURCE\ssScene.h"

namespace ss
{
	class UIScene : public Scene
	{
	public:
		UIScene();
		virtual ~UIScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void UI_Setting();
		void TextureSetting();

	private:
		class Cursor* cursor;

		class Camera* mMainCamera;
		class Camera* mPlayerCamera;
		class Camera* mUICamera;
		class Camera* mCursorCamera;
		class Camera* mInventoryCamera;
	};
}
