#include "ssSkillTree.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssSkillSelectBox.h"
#include "ssInput.h"
#include "ssDim.h"
#include "ssFontWrapper.h"
#include "ssSkillPointText.h"
#include "ssFontWrapper.h"
#include "ssSkillIcon.h"
#include "ssSkillLevel.h"
#include "ssNumber.h"
#include "ssPlayerScript.h"
#include "ssCursor.h"

namespace ss
{
	UINT ss::SkillTree::mSkillPoint = 5;
	UINT ss::SkillTree::mFireWallLevel = 0;
	UINT ss::SkillTree::mFireAuraLevel = 0;
	UINT ss::SkillTree::mHydraLevel = 0;
	UINT ss::SkillTree::mMeteorLevel = 0;
	UINT ss::SkillTree::mTelePortLevel = 0;
	

	SkillTree::SkillTree(GameObject* parent)
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

		//icon
		{
			mSkillIcon[0] = new SkillIcon(this);
			MeshRenderer* renderer = mSkillIcon[0]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"FireAuraIconMater"));
			mSkillIcon[0]->GetComponent<Transform>()->SetPosition(Vector3(-1.f, 1.0f, 0.55f));
			AddOtherGameObject(mSkillIcon[0], eLayerType::UI);
			mSkillIcon[0]->SetAble(true);

			mLevel[0] = new SkillLevel(this);
			mLevel[0]->GetComponent<Transform>()->SetPosition(Vector3(-0.92f, 0.92f, 0.54f));
			AddOtherGameObject(mLevel[0], eLayerType::UI);

			mLevelNumber[0] = new Number(this);
			mLevelNumber[0]->SetNum(0);
			mLevelNumber[0]->GetComponent<Transform>()->SetPosition(Vector3(-0.92f, 0.92f, 0.53f));
			AddOtherGameObject(mLevelNumber[0], eLayerType::UI);
		}
		{
			mSkillIcon[1] = new SkillIcon(this);
			MeshRenderer* renderer = mSkillIcon[1]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"FireWallIconBlackMater"));
			mSkillIcon[1]->GetComponent<Transform>()->SetPosition(Vector3(-1.f, 0.3f, 0.55f));
			AddOtherGameObject(mSkillIcon[1], eLayerType::UI);

			mLevel[1] = new SkillLevel(this);
			mLevel[1]->GetComponent<Transform>()->SetPosition(Vector3(-0.92f, 0.2f, 0.54f));
			AddOtherGameObject(mLevel[1], eLayerType::UI);

			mLevelNumber[1] = new Number(this);
			mLevelNumber[1]->SetNum(0);
			mLevelNumber[1]->GetComponent<Transform>()->SetPosition(Vector3(-0.92f, 0.2f, 0.53f));
			AddOtherGameObject(mLevelNumber[1], eLayerType::UI);
		}
		{
			mSkillIcon[2] = new SkillIcon(this);
			MeshRenderer* renderer = mSkillIcon[2]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"MeteorIconBlackMater"));
			mSkillIcon[2]->GetComponent<Transform>()->SetPosition(Vector3(-1.f, -0.4f, 0.55f));
			AddOtherGameObject(mSkillIcon[2], eLayerType::UI);

			mLevel[2] = new SkillLevel(this);
			mLevel[2]->GetComponent<Transform>()->SetPosition(Vector3(-0.92f, -0.52f, 0.54f));
			AddOtherGameObject(mLevel[2], eLayerType::UI);

			mLevelNumber[2] = new Number(this);
			mLevelNumber[2]->SetNum(0);
			mLevelNumber[2]->GetComponent<Transform>()->SetPosition(Vector3(-0.92f, -0.52f, 0.53f));
			AddOtherGameObject(mLevelNumber[2], eLayerType::UI);
		}
		{
			mSkillIcon[3] = new SkillIcon(this);
			MeshRenderer* renderer = mSkillIcon[3]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"HydraIconBlackMater"));
			mSkillIcon[3]->GetComponent<Transform>()->SetPosition(Vector3(-0.4f, 0.3f, 0.55f));
			AddOtherGameObject(mSkillIcon[3], eLayerType::UI);

			mLevel[3] = new SkillLevel(this);
			mLevel[3]->GetComponent<Transform>()->SetPosition(Vector3(-0.32f, 0.2f, 0.54f));
			AddOtherGameObject(mLevel[3], eLayerType::UI);

			mLevelNumber[3] = new Number(this);
			mLevelNumber[3]->SetNum(0);
			mLevelNumber[3]->GetComponent<Transform>()->SetPosition(Vector3(-0.32f, 0.2f, 0.53f));
			AddOtherGameObject(mLevelNumber[3], eLayerType::UI);
		}
		{
			mSkillIcon[4] = new SkillIcon(this);
			MeshRenderer* renderer = mSkillIcon[4]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"TelePortIconBlackMater"));
			mSkillIcon[4]->GetComponent<Transform>()->SetPosition(Vector3(-0.4f, -0.4f, 0.55f));
			AddOtherGameObject(mSkillIcon[4], eLayerType::UI);

			mLevel[4] = new SkillLevel(this);
			mLevel[4]->GetComponent<Transform>()->SetPosition(Vector3(-0.32f, -0.52f, 0.54f));
			AddOtherGameObject(mLevel[4], eLayerType::UI);

			mLevelNumber[4] = new Number(this);
			mLevelNumber[4]->SetNum(0);
			mLevelNumber[4]->GetComponent<Transform>()->SetPosition(Vector3(-0.32f, -0.52f, 0.53f));
			AddOtherGameObject(mLevelNumber[4], eLayerType::UI);
		}

		//invalidIcon
		{
			mInvalidIcon[0] = new SkillIcon(this);
			MeshRenderer* renderer = mInvalidIcon[0]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"SkillIcon1Mater"));
			mInvalidIcon[0]->GetComponent<Transform>()->SetPosition(Vector3(0.3f, 1.0f, 0.55f));
			AddOtherGameObject(mInvalidIcon[0], eLayerType::UI);

			mLevel[5] = new SkillLevel(this);
			mLevel[5]->GetComponent<Transform>()->SetPosition(Vector3(0.4f, 0.92f, 0.54f));
			AddOtherGameObject(mLevel[5], eLayerType::UI);

			mLevelNumber[5] = new Number(this);
			mLevelNumber[5]->SetNum(0);
			mLevelNumber[5]->GetComponent<Transform>()->SetPosition(Vector3(0.4f, 0.92f, 0.53f));
			AddOtherGameObject(mLevelNumber[5], eLayerType::UI);
		}
		{
			mInvalidIcon[1] = new SkillIcon(this);
			MeshRenderer* renderer = mInvalidIcon[1]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"SkillIcon2Mater"));
			mInvalidIcon[1]->GetComponent<Transform>()->SetPosition(Vector3(0.3f, 0.3f, 0.55f));
			AddOtherGameObject(mInvalidIcon[1], eLayerType::UI);

			mLevel[6] = new SkillLevel(this);
			mLevel[6]->GetComponent<Transform>()->SetPosition(Vector3(0.4f, 0.2f, 0.54f));
			AddOtherGameObject(mLevel[6], eLayerType::UI);

			mLevelNumber[6] = new Number(this);
			mLevelNumber[6]->SetNum(0);
			mLevelNumber[6]->GetComponent<Transform>()->SetPosition(Vector3(0.4f, 0.2f, 0.53f));
			AddOtherGameObject(mLevelNumber[6], eLayerType::UI);
		}
		{
			mInvalidIcon[2] = new SkillIcon(this);
			MeshRenderer* renderer = mInvalidIcon[2]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"SkillIcon3Mater"));
			mInvalidIcon[2]->GetComponent<Transform>()->SetPosition(Vector3(0.3f, -0.4f, 0.55f));
			AddOtherGameObject(mInvalidIcon[2], eLayerType::UI);

			mLevel[7] = new SkillLevel(this);
			mLevel[7]->GetComponent<Transform>()->SetPosition(Vector3(0.4f, -0.52f, 0.54f));
			AddOtherGameObject(mLevel[7], eLayerType::UI);

			mLevelNumber[7] = new Number(this);
			mLevelNumber[7]->SetNum(0);
			mLevelNumber[7]->GetComponent<Transform>()->SetPosition(Vector3(0.4f, -0.52f, 0.53f));
			AddOtherGameObject(mLevelNumber[7], eLayerType::UI);
		}
		{
			mInvalidIcon[3] = new SkillIcon(this);
			MeshRenderer* renderer = mInvalidIcon[3]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"SkillIcon4Mater"));
			mInvalidIcon[3]->GetComponent<Transform>()->SetPosition(Vector3(0.9f, 0.3f, 0.55f));
			AddOtherGameObject(mInvalidIcon[3], eLayerType::UI);

			mLevel[8] = new SkillLevel(this);
			mLevel[8]->GetComponent<Transform>()->SetPosition(Vector3(1.f, 0.2f, 0.54f));
			AddOtherGameObject(mLevel[8], eLayerType::UI);

			mLevelNumber[8] = new Number(this);
			mLevelNumber[8]->SetNum(0);
			mLevelNumber[8]->GetComponent<Transform>()->SetPosition(Vector3(1.f, 0.2f, 0.53f));
			AddOtherGameObject(mLevelNumber[8], eLayerType::UI);
		}
		{
			mInvalidIcon[4] = new SkillIcon(this);
			MeshRenderer* renderer = mInvalidIcon[4]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"SkillIcon5Mater"));
			mInvalidIcon[4]->GetComponent<Transform>()->SetPosition(Vector3(0.9f, -0.4f, 0.55f));
			AddOtherGameObject(mInvalidIcon[4], eLayerType::UI);

			mLevel[9] = new SkillLevel(this);
			mLevel[9]->GetComponent<Transform>()->SetPosition(Vector3(1.f, -0.52f, 0.54f));
			AddOtherGameObject(mLevel[9], eLayerType::UI);

			mLevelNumber[9] = new Number(this);
			mLevelNumber[9]->SetNum(0);
			mLevelNumber[9]->GetComponent<Transform>()->SetPosition(Vector3(1.f, -0.52f, 0.53f));
			AddOtherGameObject(mLevelNumber[9], eLayerType::UI);
		}

		//skillpoint
		mLevelNumber[10] = new Number(this);
		mLevelNumber[10]->SetNum(0);
		mLevelNumber[10]->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.1f, 1.f));
		mLevelNumber[10]->GetComponent<Transform>()->SetPosition(Vector3(-0.94f, -1.f, 0.53f));
		AddOtherGameObject(mLevelNumber[10], eLayerType::UI);
		
		//stem
		{
			mLine[0] = new SkillIcon(this);
			MeshRenderer* renderer = mLine[0]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"RedLineMater"));
			mLine[0]->GetComponent<Transform>()->SetPosition(Vector3(-1.f, 0.3f, 0.555f));
			mLine[0]->GetComponent<Transform>()->SetScale(Vector3(0.15f, 1.5f, 1.f));
			AddOtherGameObject(mLine[0], eLayerType::UI);
		}
		{
			mLine[1] = new SkillIcon(this);
			MeshRenderer* renderer = mLine[1]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"RedLineMater"));
			mLine[1]->GetComponent<Transform>()->SetPosition(Vector3(-0.7f, 0.65f, 0.556f));
			mLine[1]->GetComponent<Transform>()->SetScale(Vector3(0.15f, 0.8f, 1.f));
			mLine[1]->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, 0.88f));
			AddOtherGameObject(mLine[1], eLayerType::UI);
		}
		{
			mLine[2] = new SkillIcon(this);
			MeshRenderer* renderer = mLine[2]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"RedLineMater"));
			mLine[2]->GetComponent<Transform>()->SetPosition(Vector3(-0.4f, -0.1f, 0.555f));
			mLine[2]->GetComponent<Transform>()->SetScale(Vector3(0.15f, 0.7f, 1.f));
			AddOtherGameObject(mLine[2], eLayerType::UI);
		}
		{
			mLine[3] = new SkillIcon(this);
			MeshRenderer* renderer = mLine[3]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"RedLineMater"));
			mLine[3]->GetComponent<Transform>()->SetPosition(Vector3(0.3f, 0.3f, 0.555f));
			mLine[3]->GetComponent<Transform>()->SetScale(Vector3(0.15f, 1.5f, 1.f));
			AddOtherGameObject(mLine[3], eLayerType::UI);
		}
		{
			mLine[4] = new SkillIcon(this);
			MeshRenderer* renderer = mLine[4]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"RedLineMater"));
			mLine[4]->GetComponent<Transform>()->SetPosition(Vector3(0.6f, 0.65f, 0.556f));
			mLine[4]->GetComponent<Transform>()->SetScale(Vector3(0.15f, 0.8f, 1.f));
			mLine[4]->GetComponent<Transform>()->SetRotation(Vector3(0.f, 0.f, 0.88f));
			AddOtherGameObject(mLine[4], eLayerType::UI);
		}
		{
			mLine[5] = new SkillIcon(this);
			MeshRenderer* renderer = mLine[5]->GetComponent<MeshRenderer>();
			renderer->SetMaterial(Resources::Find<Material>(L"RedLineMater"));
			mLine[5]->GetComponent<Transform>()->SetPosition(Vector3(0.9f, -0.1f, 0.555f));
			mLine[5]->GetComponent<Transform>()->SetScale(Vector3(0.15f, 0.7f, 1.f));
			AddOtherGameObject(mLine[5], eLayerType::UI);
		}
		

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
		SetClickCheck();

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

				for (int i = 0; i < 6; i++)
				{
					mLine[i]->SetOnOff(false);
				}
				for (int i = 0; i < 5; i++)
				{
					mSkillIcon[i]->SetOnOff(false);
					mInvalidIcon[i]->SetOnOff(false);
				}
				for (int i = 0; i < 10; i++)
				{
					mLevel[i]->SetOnOff(false);
				}
				for (int i = 0; i < 11; i++)
				{
					mLevelNumber[i]->SetOnOff(false);
				}
			}
			else
			{
				mOn = true;
				mDim->SetOnOff(true);
				mText->SetOnOff(true);
				Renew();

				for (int i = 0; i < 6; i++)
				{
					mLine[i]->SetOnOff(true);
				}
				for (int i = 0; i < 5; i++)
				{
					mSkillIcon[i]->SetOnOff(true);
					mInvalidIcon[i]->SetOnOff(true);
				}
				for (int i = 0; i < 10; i++)
				{
					mLevel[i]->SetOnOff(true);
				}
				for (int i = 0; i < 11; i++)
				{
					mLevelNumber[i]->SetOnOff(true);
				}
			}
		}
	}

	void SkillTree::SetClickCheck()
	{
		if (mSkillPoint <= 0)
			return;
		
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			for (int i = 0; i < 5; i++)
			{
				Vector2 LBpos = mSkillIcon[i]->GetComponent<Transform>()->GetWorldLeftBottom();
				Vector2 RTpos = mSkillIcon[i]->GetComponent<Transform>()->GetWorldRightUp();
				Vector3 cursorPos = Cursor::GetPos() - PlayerScript::GetPlayerPos();

				if (LBpos.x <= cursorPos.x && cursorPos.x <= RTpos.x
					&& LBpos.y <= cursorPos.y && cursorPos.y <= RTpos.y)
				{
					if (!mSkillIcon[i]->GetAble())
						continue;

					if (i == 0)
					{
						mFireAuraLevel++;
						mLevelNumber[i]->SetNum(mFireAuraLevel);
					}
					else if (i == 1)
					{
						mFireWallLevel++;
						mLevelNumber[i]->SetNum(mFireWallLevel);
					}
					else if (i == 2)
					{
						mMeteorLevel++;
						mLevelNumber[i]->SetNum(mMeteorLevel);
					}
					else if (i == 3)
					{
						mHydraLevel++;
						mLevelNumber[i]->SetNum(mHydraLevel);
					}
					else if (i == 4)
					{
						mTelePortLevel++;
						mLevelNumber[i]->SetNum(mTelePortLevel);
					}

					mSkillPoint--;
					mLevelNumber[10]->SetNum(mSkillPoint);

					break;
				}
				
			}
		}

		LearnCheck();
	}

	void SkillTree::LearnCheck()
	{
		if (mFireAuraLevel > 0)
		{
			mSkillIcon[1]->GetComponent<MeshRenderer>()
				->SetMaterial(Resources::Find<Material>(L"FireWallMater"));
			mSkillIcon[1]->SetAble(true);

			mSkillIcon[3]->GetComponent<MeshRenderer>()
				->SetMaterial(Resources::Find<Material>(L"HydraIconMater"));
			mSkillIcon[3]->SetAble(true);
		}

		if (mFireWallLevel > 0)
		{
			mSkillIcon[2]->GetComponent<MeshRenderer>()
				->SetMaterial(Resources::Find<Material>(L"MeteorIconMater"));
			mSkillIcon[2]->SetAble(true);
		}

		if (mHydraLevel > 0)
		{
			mSkillIcon[4]->GetComponent<MeshRenderer>()
				->SetMaterial(Resources::Find<Material>(L"TelePortIconMater"));
			mSkillIcon[4]->SetAble(true);
		}

	}

	void SkillTree::Renew()
	{
		LearnCheck();
		mLevelNumber[10]->SetNum(mSkillPoint);
		mLevelNumber[0]->SetNum(mFireAuraLevel);
		mLevelNumber[1]->SetNum(mFireWallLevel);
		mLevelNumber[2]->SetNum(mMeteorLevel);
		mLevelNumber[3]->SetNum(mHydraLevel);
		mLevelNumber[4]->SetNum(mTelePortLevel);
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