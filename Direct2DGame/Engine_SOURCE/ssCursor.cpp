#include "ssCursor.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCamera.h"


namespace ss
{
	Vector3 ss::Cursor::mPos = {};
	
	Cursor::Cursor()
	{
		SetName(L"Cursor");
		mTransform = GetComponent<Transform>();

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");
		//Cursor
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Cursor1", L"..\\Resources\\Texture\\UI\\Cursor1.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				spriteMaterial->SetShader(spriteShader);
				spriteMaterial->SetTexture(texture);
				Resources::Insert(L"Cursor1Mater", spriteMaterial);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Cursor2", L"..\\Resources\\Texture\\UI\\Cursor2.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				spriteMaterial->SetShader(spriteShader);
				spriteMaterial->SetTexture(texture);
				Resources::Insert(L"Cursor2Mater", spriteMaterial);
			}
		}

		mMr = AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Find<Material>(L"Cursor1Mater"));
		mTransform->SetScale(Vector3(0.2f, 0.2f, 1.0f));
		//mTransform->SetPosition(Vector3::Zero);
		mOffset = Vector3(0.09f, -0.09f, 0.0f);
	}
	Cursor::~Cursor()
	{
	}
	void Cursor::Initialize()
	{
		GameObject::Initialize();
	}
	void Cursor::Update()
	{
		GameObject::Update();

		Viewport viewport;
		viewport.width = 1200.0f;
		viewport.height = 700.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		mPos.x = Input::GetMousePos().x;
		mPos.y = Input::GetMousePos().y;
		mPos.z = 0.00f;

		mPos = viewport.Unproject(mPos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		mPos += mOffset;

		mTransform->SetPosition(mPos); //indicator¿ë

		if(Input::GetKey(eKeyCode::LBUTTON))
			mMr->SetMaterial(Resources::Find<Material>(L"Cursor2Mater"));
		else
			mMr->SetMaterial(Resources::Find<Material>(L"Cursor1Mater"));
	}
	void Cursor::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Cursor::Render()
	{
		GameObject::Render();
	}
	
}
