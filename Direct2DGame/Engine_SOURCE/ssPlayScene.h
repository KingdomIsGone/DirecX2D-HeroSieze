#pragma once
#include "ssScene.h"

namespace ss
{
	class PlayScene : public Scene
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}