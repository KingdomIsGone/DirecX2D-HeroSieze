#include "ssSkillTree.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssSkillSelectBox.h"
#include "ssInput.h"
#include "ssDim.h"
#include "ssFontWrapper.h"
#include "ssSkillPointText.h"
#include "ssFontWrapper.h"

namespace ss
{
	SkillTree::SkillTree(GameObject* parent)
		: mSkillPoint(15)
	{
		SetParent(parent);
		mTransform = GetComponent<Transform>();

		mTransform->SetScale(Vector3(3.f, 3.f, 1.f));

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"SkillTreeMater")); 
		
		mText = new SkillPointText(this);
		mText->GetComponent<Transform>()->SetPosition(Vector3(-1.2f, -1.f, 0.55f));
		AddOtherGameObject(mText, eLayerType::UI);

	}

	SkillTree::~SkillTree()
	{
	}

	void SkillTree::Initialize()
	{
		GameObject::Initialize();
	}
	void SkillTree::Update()
	{
		GameObject::Update();

		SetOnOffCheck();

	}
	void SkillTree::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void SkillTree::Render()
	{
		if (mOn)
		{
			GameObject::Render();
			
			
			FontWrapper::DrawFont(IntToWchar(mSkillPoint), 400, 538, 20, FONT_RGBA(255, 255, 255, 255));
		}

	}

	void SkillTree::SetOnOffCheck()
	{
		if (Input::GetKeyDown(eKeyCode::T))
		{
			if (mOn)
			{
				mOn = false;
				mDim->SetOnOff(false);
				mText->SetOnOff(false);
			}
			else
			{
				mOn = true;
				mDim->SetOnOff(true);
				mText->SetOnOff(true);
			}
		}
	}

	wchar_t* SkillTree::IntToWchar(int num)
	{
		int digitOne = num % 10;
		int digitTen = ((num % 100) - digitOne)/10;

		char ten = digitTen + '0';
		char one = digitOne + '0';

		char number[3];
		number[0] = ten;
		number[1] = one;
		
		size_t numberSize = 100;
		wchar_t* wc = new wchar_t[100];
		mbstowcs_s(&numberSize, wc, 100, number, 2);

		return wc;
	}

}