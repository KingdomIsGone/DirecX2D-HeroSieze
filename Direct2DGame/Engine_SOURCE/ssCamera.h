#pragma once
#include "ssComponent.h"
#include "ssGraphics.h"

namespace ss
{
	class Camera : public Component
	{
	public:
		Camera();
		~Camera();

	private:
		static Matrix mView;
		static Matrix mProjection;
	};
}
