#pragma once
#include "..\Engine_SOURCE\ssScene.h"

namespace ss
{
	class WoodsField : public Scene
	{
	public:
		WoodsField();
		virtual ~WoodsField();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
