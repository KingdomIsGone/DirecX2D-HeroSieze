#pragma once
#include "..\Engine_SOURCE\ssScene.h"

namespace ss
{
	class DesertBossRoom : public Scene
	{
	public:
		DesertBossRoom();
		virtual ~DesertBossRoom();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
