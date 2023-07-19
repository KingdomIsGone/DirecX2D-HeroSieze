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

	private:

	};
}
