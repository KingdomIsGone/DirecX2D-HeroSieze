#pragma once
#include "..\Engine_SOURCE\ssScene.h"

namespace ss
{
	class DesertDungeon2 : public Scene
	{
	public:
		DesertDungeon2();
		virtual ~DesertDungeon2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}