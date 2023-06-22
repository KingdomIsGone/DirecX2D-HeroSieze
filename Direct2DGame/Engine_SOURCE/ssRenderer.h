#pragma once
#include "ssEngine.h"
#include "ssGraphicDevice_Dx11.h"
#include "ssMesh.h"
#include "ssShader.h"
#include "ssConstantBuffer.h"

using namespace ss::math;
using namespace ss::graphics;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};
	
	extern Vertex vertexes[];
	extern ss::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];


	void Initialize();
	void Release();
}

