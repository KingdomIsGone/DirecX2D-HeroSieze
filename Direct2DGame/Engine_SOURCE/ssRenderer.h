#pragma once
#include "ssEngine.h"
#include "ssGraphicDevice_Dx11.h"
#include "ssMesh.h"
#include "ssShader.h"
#include "ssConstantBuffer.h"

using namespace ss::math;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};
	struct Transform
	{
		Vector4 Pos;
		Vector4 Color;
		Vector4 Scale;
	};
	
	extern Vertex vertexes[];
	extern ss::Mesh* mesh;
	extern ss::Shader* shader;
	extern ss::graphics::ConstantBuffer* constantBuffer;

	extern float x;
	extern float y;



	void Initialize();
	void Release();


}

