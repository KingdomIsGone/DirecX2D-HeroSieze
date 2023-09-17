#include "ssRenderer.h"
#include "ssResources.h"
#include "ssTexture.h"
#include "ssMaterial.h"
#include "ssStructedBuffer.h"
#include "ssPaintShader.h"
#include "ssParticleShader.h"
#include "ssCamera.h"


namespace renderer
{
	using namespace ss;
	using namespace ss::graphics;

	ss::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	//
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};
	
	// light
	std::vector<Light*> lights = {};
	StructedBuffer* lightsBuffer = nullptr;
	LightAttribute lightNormalAttribute = {}; //custom
	

	//
	ss::Camera* mainCamera = nullptr;
	std::vector<ss::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};

	void SetupState()
	{
		//custom
		lightNormalAttribute.color = Vector4(0.0f, .0f, .0f, 1.0f);
#pragma region InputLayout
		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = ss::Resources::Find<Shader>(L"TriangleShader");
		ss::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = ss::Resources::Find<Shader>(L"SpriteShader");
		ss::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = ss::Resources::Find<Shader>(L"GridShader");
		ss::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = ss::Resources::Find<Shader>(L"DebugShader");
		ss::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = ss::Resources::Find<Shader>(L"SpriteAnimationShader");
		ss::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = ss::Resources::Find<Shader>(L"ParticleShader");
		ss::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
#pragma endregion
#pragma region Sampler State
		//Sampler State
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());  //안보이는 뒤 자르기

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf()); // 앞 자르기

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());  //no culling

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());  //와이어 프레임
#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		//less
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;  // z값을 비교해 더 작은(더 앞에 있는)것을 그려준다
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false; // 스텐실 기법 쓸지 거울 만들떄 씀

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		//Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		//No Write
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		//None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		D3D11_BLEND_DESC blendDesc = {};
		
		//default 아무것도 안함
		blendStates[(UINT)eBSType::Default] = nullptr;
		
		// Alpha Blend 뒤에 물체 앞에 물체 섞기
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;   //렌더타겟 0의 설정만 사용
		blendDesc.RenderTarget[0].BlendEnable = true;  //블렌드 할지 말지
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;   // Source:쉐이더에서 출력할 텍스쳐 픽셀
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;  // Destination: 렌더타겟
		//알파 = (SrcAlpha * SrcBlendAlpha) BlendOpAlpha (DestAlpha * DestBlendAlpha) 알파값 지정
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD; 
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one 알파값없이 더하기
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion


	}

	void LoadMesh()
	{
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};


		// PointMesh
		Vertex v = {};
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes.push_back(v);
		indexes.push_back(0);
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"PointMesh", mesh);


		vertexes.clear();
		indexes.clear();

		//RECT
		vertexes.resize(4);
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);


		// Vertex Buffer
		mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Rect Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertexes.push_back(center);
		}


		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());
	}

	void LoadBuffer()
	{

		// Constant Buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Grid Buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(TransformCB));

		// Animation Buffer
		constantBuffer[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		// Debug Buffer custom
		constantBuffer[(UINT)eCBType::Debug] = new ConstantBuffer(eCBType::Debug);
		constantBuffer[(UINT)eCBType::Debug]->Create(sizeof(DebugCB));

		//ParticleCB
		constantBuffer[(UINT)eCBType::Particle] = new ConstantBuffer(eCBType::Particle);
		constantBuffer[(UINT)eCBType::Particle]->Create(sizeof(ParticleCB));

		//NoiseCB
		constantBuffer[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffer[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

		// light structed buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 2, eViewType::SRV, nullptr, true);

	}

	void LoadShader()
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();

		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		ss::Resources::Insert(L"TriangleShader", shader);

		shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		ss::Resources::Insert(L"SpriteShader", shader);

		std::shared_ptr<Shader> spriteAniShader = std::make_shared<Shader>();
		spriteAniShader->Create(eShaderStage::VS, L"SpriteAnimationVS.hlsl", "main");
		spriteAniShader->Create(eShaderStage::PS, L"SpriteAnimationPS.hlsl", "main");
		ss::Resources::Insert(L"SpriteAnimationShader", spriteAniShader);

		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		ss::Resources::Insert(L"GridShader", gridShader);
			
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		debugShader->SetRSState(eRSType::WireframeNone);
		ss::Resources::Insert(L"DebugShader", debugShader);
		
		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		ss::Resources::Insert(L"PaintShader", paintShader);

		std::shared_ptr<ParticleShader> psSystemShader = std::make_shared<ParticleShader>();
		psSystemShader->Create(L"ParticleCS.hlsl", "main");
		ss::Resources::Insert(L"ParticleSystemShader", psSystemShader);

		std::shared_ptr<Shader> paritcleShader = std::make_shared<Shader>();
		paritcleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		paritcleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		paritcleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		paritcleShader->SetRSState(eRSType::SolidNone);
		paritcleShader->SetDSState(eDSType::NoWrite);
		paritcleShader->SetBSState(eBSType::AlphaBlend);
		paritcleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		ss::Resources::Insert(L"ParticleShader", paritcleShader);
	}

	void LoadTexture()
	{
		//paint texture
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		ss::Resources::Insert(L"PaintTexuture", uavTexture);

		std::shared_ptr<Texture> particle = std::make_shared<Texture>();
		Resources::Load<Texture>(L"CartoonSmoke", L"..\\Resources\\particle\\CartoonSmoke.png");

		Resources::Load<Texture>(L"Noise01", L"..\\Resources\\noise\\noise_01.png");
		Resources::Load<Texture>(L"Noise02", L"..\\Resources\\noise\\noise_02.png");
		Resources::Load<Texture>(L"Noise03", L"..\\Resources\\noise\\noise_03.png");
	}

	void LoadMaterial()
	{
		std::shared_ptr<Shader> shader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> texture
			= Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		Resources::Insert(L"SpriteMaterial", material);

		//texture = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		texture = Resources::Find<Texture>(L"PaintTexuture");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteMaterial02", material);

		std::shared_ptr<Shader> AnimationShader
			= Resources::Find<Shader>(L"SpriteAnimationShader");
		material = std::make_shared<Material>();
		material->SetShader(AnimationShader);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteAnimationMaterial", material);

		std::shared_ptr<Shader> gridShader
			= Resources::Find<Shader>(L"GridShader");

		material = std::make_shared<Material>();
		material->SetShader(gridShader);
		Resources::Insert(L"GridMaterial", material);

		std::shared_ptr<Shader> debugShader
			= Resources::Find<Shader>(L"DebugShader");

		material = std::make_shared<Material>();
		material->SetShader(debugShader);
		Resources::Insert(L"DebugMaterial", material);

		shader
			= Resources::Find<Shader>(L"ParticleShader");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetRenderingMode(eRenderingMode::Transparent);

		std::shared_ptr<Texture> particleTexx
			= Resources::Find<Texture>(L"CartoonSmoke");
		material->SetTexture(particleTexx);
		Resources::Insert(L"ParticleMaterial", material);

		//std::shared_ptr<Shader> debugShader
		//	= Resources::Find<Shader>(L"DebugShader");

		//material = std::make_shared<Material>();
		//material->SetShader(debugShader);
		//Resources::Insert(L"PaintMaterial", material);

		////UI
		
		shader
			= Resources::Find<Shader>(L"SpriteShader");
		//캐릭터 및 레벨창 z=1.01
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"CharacterCircle", L"..\\Resources\\Texture\\UI\\CharacterCircle.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"CharacterCircle0", spriteMateiral);
			}
		}

		//HPMP Bar z=1.01
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"HPMPBarTex", L"..\\Resources\\Texture\\UI\\HpMpBar.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(shader);
				spriteMaterial->SetTexture(texture);
				spriteMaterial->SetRenderingMode(eRenderingMode::CutOut);
				Resources::Insert(L"HPMPMater", spriteMaterial);
			}
		}

		//USEITEMBox z=1.01
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ItemUseTex", L"..\\Resources\\Texture\\UI\\ItemUse.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"ItemUseMater", spriteMateiral);
			}
		}

		//SkillMenu z=1.01
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"SkillMenuTex", L"..\\Resources\\Texture\\UI\\SkillMenu.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SkillMenuMater", spriteMateiral);
			}
		}

		//key z=1.005
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ttex", L"..\\Resources\\Texture\\UI\\t.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"tMater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ctex", L"..\\Resources\\Texture\\UI\\c.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"cMater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"1tex", L"..\\Resources\\Texture\\UI\\1.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"1Mater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"2tex", L"..\\Resources\\Texture\\UI\\2.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"2Mater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"3tex", L"..\\Resources\\Texture\\UI\\3.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"3Mater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"4tex", L"..\\Resources\\Texture\\UI\\4.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"4Mater", spriteMateiral);
			}

			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"vtex", L"..\\Resources\\Texture\\UI\\v.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"vMater", spriteMateiral);
			}
		}

		//MenuSet z=1.005
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"MenuSet", L"..\\Resources\\Texture\\UI\\MenuSet.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(shader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"MenuSetMater", spriteMateiral);
		}

		//ResourceBackBar z=1.005
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"ResourceBackBar", L"..\\Resources\\Texture\\UI\\ResourceBackBar.png");
				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"ResourceBackBarMater", spriteMateiral);
			}
		}

		//Portal z=1.006
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"TownPortal", L"..\\Resources\\Texture\\UI\\Hud_Town_Portal_spr.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(shader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"TownPortalMater", spriteMateiral);
		}
		std::shared_ptr<Shader> SpShader = Resources::Find<Shader>(L"SpriteShader");
		//MonsterHpBar, fill
		{
			std::shared_ptr<Texture> EnemyHpBarTex
				= Resources::Load<Texture>(L"EnemyHpBarTex", L"..\\Resources\\Texture\\UI\\Enemy_HP_Bar_spr_0.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(SpShader);
			spriteMateiral->SetTexture(EnemyHpBarTex);
			spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"EnemyHpBarMater", spriteMateiral);

			std::shared_ptr<Texture> EnemyHpBarFillRedTex
				= Resources::Load<Texture>(L"EnemyHpBarFillRedTex", L"..\\Resources\\Texture\\UI\\Small_HP_Fill_red.png");
			std::shared_ptr<Material> spriteMateiral2 = std::make_shared<Material>();
			spriteMateiral2->SetShader(SpShader);
			spriteMateiral2->SetTexture(EnemyHpBarFillRedTex);
			spriteMateiral2->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"EnemyHpBarFillRedMater", spriteMateiral2);
		}
		
		//PlayerHpSmallBar, fill
		{
			std::shared_ptr<Texture> PlayerHpSmallBarTex
				= Resources::Load<Texture>(L"PlayerHpSmallBarTex", L"..\\Resources\\Texture\\UI\\PlayerSmall_HP_Bar_spr_0.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(SpShader);
			spriteMateiral->SetTexture(PlayerHpSmallBarTex);
			spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"PlayerHpSmallBarMater", spriteMateiral);

			std::shared_ptr<Texture> PlayerHpSmallBarFillRedTex
				= Resources::Load<Texture>(L"PlayerHpSmallBarFillRedTex", L"..\\Resources\\Texture\\UI\\Small_HP_Fill_Player_spr_0.png");
			std::shared_ptr<Material> spriteMateiral2 = std::make_shared<Material>();
			spriteMateiral2->SetShader(SpShader);
			spriteMateiral2->SetTexture(PlayerHpSmallBarFillRedTex);
			spriteMateiral2->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"PlayerHpSmallBarFillRedMater", spriteMateiral2);
		}

		//보스HPBar
		{
			std::shared_ptr<Texture> BossHpBarTex
				= Resources::Load<Texture>(L"BossHpBarTex", L"..\\Resources\\Texture\\UI\\Boss_Health_Frame_spr_0.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(SpShader);
			spriteMateiral->SetTexture(BossHpBarTex);
			spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"BossHpBarMater", spriteMateiral);
		}

		//blank
		{
			std::shared_ptr<Texture> blankTex
				= Resources::Load<Texture>(L"blankTex", L"..\\Resources\\Texture\\Blank.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(SpShader);
			spriteMateiral->SetTexture(blankTex);
			spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"BlankMater", spriteMateiral);
		}

		//석관
		{
			std::shared_ptr<Texture> SarcophagusTex
				= Resources::Load<Texture>(L"SarcophagusTex", L"..\\Resources\\Texture\\Monster\\Mummy\\Sarkofagus_spr.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(SpShader);
			spriteMateiral->SetTexture(SarcophagusTex);
			spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"SarcophagusMater", spriteMateiral);
		}

		//이뮨텍스트
		{
			std::shared_ptr<Texture> ImmuneTextTex
				= Resources::Load<Texture>(L"ImmuneTextTex", L"..\\Resources\\Texture\\Text\\Immune.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(SpShader);
			spriteMateiral->SetTexture(ImmuneTextTex);
			spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"ImmuneTextMater", spriteMateiral);
		}

		//스킬 아이콘 메테오
		{
			std::shared_ptr<Texture> MeteorIconTex
				= Resources::Load<Texture>(L"MeteorIconTex", L"..\\Resources\\Texture\\Skill\\Icon\\MeteorIcon.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(MeteorIconTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"MeteorIconMater", spriteMaterial);
		}
		//스킬 아이콘 파이어월
		{
			std::shared_ptr<Texture> FireWallIconTex
				= Resources::Load<Texture>(L"FireWallIconTex", L"..\\Resources\\Texture\\Skill\\Icon\\FireWallIcon.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(FireWallIconTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"FireWallMater", spriteMaterial);
		}

		//인벤토리
		{
			std::shared_ptr<Texture> InventoryTex
				= Resources::Load<Texture>(L"InventoryTex", L"..\\Resources\\Texture\\Inventory\\totalinventory.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(InventoryTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"InventoryMater", spriteMaterial);
		}
		//인벤토리 장비슬롯
		{
			{
				std::shared_ptr<Texture> ArmorSlotTex
					= Resources::Load<Texture>(L"ArmorSlotTex", L"..\\Resources\\Texture\\Inventory\\ItemSlot\\ArmorSlot.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(ArmorSlotTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"ArmorSlotMater", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> BeltSlotTex
					= Resources::Load<Texture>(L"BeltSlotTex", L"..\\Resources\\Texture\\Inventory\\ItemSlot\\BeltSlot.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(BeltSlotTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"BeltSlotMater", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> HelmetSlotTex
					= Resources::Load<Texture>(L"HelmetSlotTex", L"..\\Resources\\Texture\\Inventory\\ItemSlot\\HelmetSlot.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(HelmetSlotTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"HelmetSlotMater", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> PortionSlotTex
					= Resources::Load<Texture>(L"PortionSlotTex", L"..\\Resources\\Texture\\Inventory\\ItemSlot\\PortionSlot.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(PortionSlotTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"PortionSlotMater", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> ShieldSlotTex
					= Resources::Load<Texture>(L"ShieldSlotTex", L"..\\Resources\\Texture\\Inventory\\ItemSlot\\ShieldSlot.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(ShieldSlotTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"ShieldSlotMater", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> ShoesSlotTex
					= Resources::Load<Texture>(L"ShoesSlotTex", L"..\\Resources\\Texture\\Inventory\\ItemSlot\\ShoesSlot.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(ShoesSlotTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"ShoesSlotMater", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> WeaponSlotTex
					= Resources::Load<Texture>(L"WeaponSlotTex", L"..\\Resources\\Texture\\Inventory\\ItemSlot\\WeaponSlot.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(WeaponSlotTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"WeaponSlotMater", spriteMaterial);
			}
		}

		//inventoryItemList
		{
			std::shared_ptr<Texture> ItemListTex
				= Resources::Load<Texture>(L"ItemListTex", L"..\\Resources\\Texture\\Inventory\\ItemList.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(ItemListTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"ItemListMater", spriteMaterial);
		}

		//itemBackground Normal
		{
			std::shared_ptr<Texture> ItemBackNormalTex
				= Resources::Load<Texture>(L"ItemBackNormalTex", L"..\\Resources\\Texture\\Inventory\\NormalItemBack.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(ItemBackNormalTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"ItemBackNormalMater", spriteMaterial);
		}

		//itemBackground Magic
		{
			std::shared_ptr<Texture> ItemBackMagicTex
				= Resources::Load<Texture>(L"ItemBackMagicTex", L"..\\Resources\\Texture\\Inventory\\MagicItemBack.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(ItemBackMagicTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"ItemBackMagicMater", spriteMaterial);
		}

		//itemBackground Legend
		{
			std::shared_ptr<Texture> ItemBackLegendTex
				= Resources::Load<Texture>(L"ItemBackLegendTex", L"..\\Resources\\Texture\\Inventory\\LegendItemBack.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(ItemBackLegendTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"ItemBackLegendMater", spriteMaterial);
		}

	}

	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadTexture();
		LoadMaterial();
	}

	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}

	void BindLights()
	{
		std::vector<LightAttribute> lightsAttributes = {};
		for (Light* light : lights)
		{
			LightAttribute attribute = light->GetAttribute();
			lightsAttributes.push_back(attribute);
		}

		lightsBuffer->SetData(lightsAttributes.data(), lightsAttributes.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);
	}

	//custom
	void BindNormalLights()
	{
		lightsBuffer->SetData(&lightNormalAttribute, 1);
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);
	}

	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> texture
			= Resources::Find<Texture>(L"Noise01");

		texture->BindShaderResource(eShaderStage::VS, 15);
		texture->BindShaderResource(eShaderStage::HS, 15);
		texture->BindShaderResource(eShaderStage::DS, 15);
		texture->BindShaderResource(eShaderStage::GS, 15);
		texture->BindShaderResource(eShaderStage::PS, 15);
		texture->BindShaderResource(eShaderStage::CS, 15);

		ConstantBuffer* cb = constantBuffer[(UINT)eCBType::Noise];
		NoiseCB data = {};
		data.size.x = texture->GetWidth();
		data.size.y = texture->GetHeight();

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}

	void Render()
	{
		BindNoiseTexture();
		BindLights();

		Camera* inventoryCamera = nullptr;
		Camera* CursorCamera = nullptr;
		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;
			//custom
			if (cam->GetName() == L"InventoryCamera")
			{
				inventoryCamera = cam;
				continue;
			}
			else if (cam->GetName() == L"CursorCamera")
			{
				CursorCamera = cam;
				continue;
			}

			cam->Render();
		}
		lights.clear();
		BindNormalLights();

		if(inventoryCamera != nullptr)
			inventoryCamera->Render();
		if (CursorCamera != nullptr)
			CursorCamera->Render();

		lights.clear();
		cameras.clear();
	}

	void Release()
	{
		for ( ConstantBuffer* buff : constantBuffer )
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}
}



