#include "ssMiniMap.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssShader.h"
#include "ssPlayerScript.h"
#include "ssConstantBuffer.h"
#include "ssRenderer.h"
#include "ssTime.h"

namespace ss
{
	MiniMap::MiniMap()
		: mXmoveAmount(0.f)
		, mYmoveAmount(0.f)
	{
		mTransform = GetComponent<Transform>();
		
		mMeshRenderer = AddComponent<MeshRenderer>();
		mMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		
		mMapDot = new GameObject();
		mMapDot->GetComponent<Transform>()->SetScale(0.05f, 0.05f, 1.f);
		mMapDot->GetComponent<Transform>()->SetPosition(2.5f, 1.3f, 0.73f);
		MeshRenderer* mr = mMapDot->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MapDot"));
		AddOtherGameObject(mMapDot, eLayerType::UI);

	}
	MiniMap::~MiniMap()
	{
	}
	void MiniMap::Initialize()
	{
		GameObject::Initialize();
	}
	void MiniMap::Update()
	{
		GameObject::Update();

		CalUVPos();
		BindCB();

		mPos = mTransform->GetPosition();
		mPos.x -= mXmoveAmount *4450.f * Time::DeltaTime();  
		mPos.y += mYmoveAmount * 3380.f * Time::DeltaTime();
		mTransform->SetPosition(mPos);

	}
	void MiniMap::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MiniMap::Render()
	{
		GameObject::Render();
	}

	void MiniMap::SetMiniMap(std::wstring name, float Width, float Height)
	{
		mTextureName = name;
		float modify = Width / Height;
		mTransform->SetScale(Vector3(3.f * modify, 3.f, 1.0f));  
		std::shared_ptr<ss::Shader> miniMapShader = Resources::Find<Shader>(L"MiniMapShader");

		std::shared_ptr<Texture> texture
			= Resources::Find<Texture>(mTextureName);

		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(miniMapShader);
		material->SetTexture(texture);

		
		mMeshRenderer->SetMaterial(material);
	}

	void MiniMap::CalUVPos()
	{
		mPlayerPos = PlayerScript::GetPlayerPos();

		mPrevUVPos = mUVPos;

		float tempX = mRatioWidth / 2.f + mPlayerPos.x;
		mUVPos.x = tempX / mRatioWidth;
		float tempY = mRatioHeight / 2.f - mPlayerPos.y;
		mUVPos.y = tempY / mRatioHeight;

		mXmoveAmount = mUVPos.x - mPrevUVPos.x;
		mYmoveAmount = mUVPos.y - mPrevUVPos.y;

		mPrevUVPos = mUVPos;
	}

	void MiniMap::BindCB()
	{
		ss::graphics::ConstantBuffer* cb
			= renderer::constantBuffer[(int)eCBType::Debug];

		renderer::DebugCB data;
		
		data.UVpos = mUVPos;

		cb->SetData(&data);

		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::VS);
	}

	
}
