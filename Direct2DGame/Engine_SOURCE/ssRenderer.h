#pragma once
#include "ssEngine.h"
#include "ssGraphicDevice_Dx11.h"
#include "ssMesh.h"
#include "ssShader.h"
#include "ssConstantBuffer.h"
#include "ssCamera.h"
#include "ssLight.h"


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

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)   //16바이트 단위로 정렬
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		Vector2 spriteLeftTop;
		Vector2 spriteSize;
		Vector2 spriteOffset;
		Vector2 atlasSize;
		UINT animationType;
	};

	CBUFFER(ParticleCB, CBSLOT_PARTICLE)
	{
		UINT elementCount;
		float elpasedTime;
		float deltaTime;
		int padd2;
	};

	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 size;
	};

	CBUFFER(DebugCB, CBSLOT_DEBUG)  //custom
	{
		Vector4 debugColor;
	};

	CBUFFER(CoolTimeCB, CBSLOT_COOLTIME)  //custom
	{
		float coolTimePercent;
	};
	CBUFFER(CoolTimeCB2, CBSLOT_COOLTIME)  //custom
	{
		float coolTimePercent;
	};
	CBUFFER(CoolTimeCB3, CBSLOT_COOLTIME)  //custom
	{
		float coolTimePercent;
	};
	CBUFFER(CoolTimeCB4, CBSLOT_COOLTIME)  //custom
	{
		float coolTimePercent;
	};
	CBUFFER(BossEffectCB, CBSLOT_COOLTIME)  //custom
	{
		float Radd;
		float Gadd;
		float Badd;
		float A;
	};

	extern ss::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<ss::Light*> lights;
	extern ss::Camera* mainCamera;
	extern std::vector<ss::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void BindLights();
	void BindNormalLights();  //custom
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh mesh);
}
