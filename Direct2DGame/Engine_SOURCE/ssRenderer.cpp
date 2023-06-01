#include "ssRenderer.h"

namespace ss::renderer
{
	Vertex vertexes[100] = {};
	int vertexCount = 0;
	
	// Input Layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;

	// Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;
	ID3D11Buffer* triangleIdxBuffer = nullptr;
	ID3D11Buffer* triangleConstantBuffer = nullptr;

	// error blob
	ID3DBlob* errorBlob = nullptr;

	// Vertex Shader code -> Binary Code
	ID3DBlob* triangleVSBlob = nullptr;

	// Vertex Shader
	ID3D11VertexShader* triangleVSShader = nullptr;

	// Pixel Shader code -> Binary Code
	ID3DBlob* trianglePSBlob = nullptr;

	// Vertex Shader
	ID3D11PixelShader* trianglePSShader = nullptr;

	void SetupState()
	{

	}

	void LoadBuffer()
	{
		// Vertex Buffer
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.ByteWidth = sizeof(Vertex) * vertexCount;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		ss::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);

		std::vector<UINT> indexes = {};
		/*indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);*/

		for (int i = 0; i < vertexCount; i++)
		{
			indexes.push_back(i);
		}
		

		// Index Buffer
		D3D11_BUFFER_DESC triangleIdxDesc = {};
		triangleIdxDesc.ByteWidth = sizeof(UINT) * indexes.size();
		triangleIdxDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		triangleIdxDesc.Usage = D3D11_USAGE_DEFAULT;
		triangleIdxDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA triangleIdxData = {};
		triangleIdxData.pSysMem = indexes.data();
		ss::graphics::GetDevice()->CreateBuffer(&triangleIdxBuffer, &triangleIdxDesc, &triangleIdxData);

		// Constant Buffer
		D3D11_BUFFER_DESC triangleCSDesc = {};
		triangleCSDesc.ByteWidth = sizeof(Vector4);
		triangleCSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		triangleCSDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleCSDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		ss::graphics::GetDevice()->CreateBuffer(&triangleConstantBuffer, &triangleCSDesc, nullptr);

		Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);
		ss::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &pos, sizeof(Vector4));
		ss::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);
		//
	}

	void LoadShader()
	{
		ss::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		vertexes[vertexCount].pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes[vertexCount++].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.0f, 0.1f, 0.0f);
		vertexes[vertexCount++].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.1f, 0.1f, 0.0f);
		vertexes[vertexCount++].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes[vertexCount++].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.1f, 0.1f, 0.0f);
		vertexes[vertexCount++].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.1f, 0.0f, 0.0f);
		vertexes[vertexCount++].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[vertexCount].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[vertexCount++].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.3f, 0.7f, 0.0f);
		vertexes[vertexCount++].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.5f, 0.9f, 0.0f);
		vertexes[vertexCount++].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[vertexCount++].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.5f, 0.9f, 0.0f);
		vertexes[vertexCount++].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[vertexCount].pos = Vector3(0.7f, 0.7f, 0.0f);
		vertexes[vertexCount++].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		SetupState();
		LoadBuffer();
		LoadShader();
	}
}
