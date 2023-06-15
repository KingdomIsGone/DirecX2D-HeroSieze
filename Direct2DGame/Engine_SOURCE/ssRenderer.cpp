#include "ssRenderer.h"

namespace renderer
{
	using namespace ss;
	using namespace ss::graphics;
	Vertex vertexes[300] = {};

	int vertexCount = 0;
	
	ss::Mesh* mesh = nullptr;
	ss::Shader* shader = nullptr;
	ss::graphics::ConstantBuffer* constantBuffer = nullptr;
	

	void SetupState()
	{
		// Input layout ���� ���� ������ �Ѱ�����Ѵ�.
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

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

		ss::graphics::GetDevice()->CreateInputLayout(arrLayout, 2
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
	}

	void LoadBuffer()
	{
		// Vertex Buffer
		mesh = new ss::Mesh();
		mesh->CreateVertexBuffer(vertexes, 300);

		std::vector<UINT> indexes = {};
		/*indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);*/

		for (int i = 0; i < vertexCount; i++)
		{
			indexes.push_back(i);
		}
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());


		
		// Constant Buffer
		constantBuffer = new ConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(Transform));

		constantBuffer->Bind(eShaderStage::VS);
	}

	void LoadShader()
	{
		shader = new ss::Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void Initialize()
	{
		vertexes[vertexCount].pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes[vertexCount++].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.0f, 0.1f, 0.0f);
		vertexes[vertexCount++].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.1f, 0.1f, 0.0f);
		vertexes[vertexCount++].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes[vertexCount++].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.1f, 0.1f, 0.0f);
		vertexes[vertexCount++].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.1f, 0.0f, 0.0f);
		vertexes[vertexCount++].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		LoadBuffer();
		LoadShader();
		SetupState();
	}


	void Release()
	{
		delete mesh;
		delete shader;
		delete constantBuffer;
	}
}
