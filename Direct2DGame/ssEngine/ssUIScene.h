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

		void UI_Setting();
		void TextureSetting();

	private:
		class Cursor* cursor;

		class Anubis* mAnubis;
		class BossHpBar* mBossHpBar;
		class BossHpFill* mBossHpFill;
	};
}
