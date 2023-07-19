#pragma once
#include "..\Engine_SOURCE\ssScene.h"

namespace ss
{
	class DesertDungeon1 : public Scene
	{
	public:
		DesertDungeon1();
		virtual ~DesertDungeon1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}