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

		mPlayerPos = PlayerScript::GetPlayerPos();
		mPrevPos = mPlayerPos;
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

		if (mPrevPos != mPlayerPos)
		{
			mXmoveAmount = mPlayerPos.x - mPrevPos.x;
			mYmoveAmount = mPlayerPos.y - mPrevPos.y;

			mPos.x -= mXmoveAmount * 0.2f;
			mPos.y += -mYmoveAmount * 0.0000000000000001f;

			mPrevPos = mPlayerPos;
		}

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
		mTransform->SetScale(Vector3(3.f * modify, 3.f, 1.0f));  //3.f
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

		float tempX = mRatioWidth / 2.f + mPlayerPos.x;
		mUVPos.x = tempX / mRatioWidth;
		float tempY = mRatioHeight / 2.f - mPlayerPos.y;
		mUVPos.y = tempY / mRatioHeight;

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
