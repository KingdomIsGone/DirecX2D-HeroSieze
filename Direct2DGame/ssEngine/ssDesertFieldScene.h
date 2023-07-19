#pragma once
#include "..\Engine_SOURCE\ssScene.h"

namespace ss
{
	class DesertFieldScene : public Scene
	{
	public:
		DesertFieldScene();
		virtual ~DesertFieldScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}

