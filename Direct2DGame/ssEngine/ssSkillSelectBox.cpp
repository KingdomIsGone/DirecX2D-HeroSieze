#include "ssSkillSelectBox.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssCursor.h"
#include "ssPlayerScript.h"
#include "ssSkillSelectImage.h"
#include "ssInput.h"
#include "ssSkillSlot.h"
#include "ssCursor.h"
#include "ssSkillTree.h"
#include "ssShader.h"

namespace ss
{
	UINT ss::SkillSelectBox::mLearnedSkillCount = 0;

	SkillSelectBox::SkillSelectBox(GameObject* obj)
		: mSelectSlotNum(-1)
	{
		SetName(L"SkillSelectBox");
		SetParent(obj);
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector3(1.f, 1.f, 1.0f));
		Vector3 pos = mTransform->GetPosition();
		pos.z -= 0.1f;
		mTransform->SetPosition(pos);

		mRenderer = AddComponent<MeshRenderer>();
		mRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mRenderer->SetMaterial(Resources::Find<Material>(L"SkillBoxMater"));

		mSkills[0].ID = (UINT)eSkillID::FireAura;
		mSkills[0].CoolTime = 0.2f;
		mSkills[0].Mater = L"FireAuraIconMater";

		mSkills[1].ID = (UINT)eSkillID::FireWall;
		mSkills[1].CoolTime = 0.14f;
		mSkills[1].Mater = L"FireWallMater";

		mSkills[2].ID = (UINT)eSkillID::Meteor;
		mSkills[2].CoolTime = 0.1f;
		mSkills[2].Mater = L"MeteorIconMater";

		mSkills[3].ID = (UINT)eSkillID::Hydra;
		mSkills[3].CoolTime = 0.2f;
		mSkills[3].Mater = L"HydraIconMater";

		for (int i = 0; i < 6; i++)
		{
			mSelectImage[i] = new SkillSelectImage(this);
			mSelectImage[i]->SetBox(this);
			AddOtherGameObject(mSelectImage[i], eLayerType::UI);
		}

		

	}

	SkillSelectBox::~SkillSelectBox()
	{
	}

	void SkillSelectBox::Initialize()
	{
		GameObject::Initialize();
	}
	void SkillSelectBox::Update()
	{
		GameObject::Update();

		ImagePositioning();
		ImageSetting();

		SlotClickCheck();

		if (mOn)
			SelectClickCheck();


	}
	void SkillSelectBox::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void SkillSelectBox::Render()
	{
		if(mOn)
			GameObject::Render();
	}

	void SkillSelectBox::ImagePositioning()
	{
		if (mLearnedSkillCount == 0)
		{
			mTransform->SetPosition(Vector3(-2.03f, -1.28f, 0.7f));
			mTransform->SetScale(Vector3(0.3f, 0.3f, 1.f));
		}
		else if (mLearnedSkillCount == 1)
		{
			mTransform->SetPosition(Vector3(-2.03f, -1.28f, 0.7f));
			mTransform->SetScale(Vector3(0.3f, 0.3f, 1.f));

			mSelectImage[0]->GetComponent<Transform>()->SetPosition(Vector3(-2.03f, -1.28f, 0.69f));
		}
		else if (mLearnedSkillCount == 2)
		{
			mTransform->SetPosition(Vector3(-1.86f, -1.28f, 0.7f));
			mTransform->SetScale(Vector3(0.56f, 0.3f, 1.f));

			mSelectImage[0]->GetComponent<Transform>()->SetPosition(Vector3(-1.99f, -1.28f, 0.69f));
			mSelectImage[1]->GetComponent<Transform>()->SetPosition(Vector3(-1.73f, -1.28f, 0.69f));
		}
		else if (mLearnedSkillCount == 3)
		{
			mTransform->SetPosition(Vector3(-1.73f, -1.28f, 0.7f));
			mTransform->SetScale(Vector3(0.83f, 0.3f, 1.f));

			mSelectImage[0]->GetComponent<Transform>()->SetPosition(Vector3(-1.99f, -1.28f, 0.69f));
			mSelectImage[1]->GetComponent<Transform>()->SetPosition(Vector3(-1.73f, -1.28f, 0.69f));
			mSelectImage[2]->GetComponent<Transform>()->SetPosition(Vector3(-1.47f, -1.28f, 0.69f));
		}
		else if (mLearnedSkillCount == 4)
		{
			mTransform->SetPosition(Vector3(-1.6f, -1.28f, 0.7f));
			mTransform->SetScale(Vector3(1.1f, 0.3f, 1.f));

			mSelectImage[0]->GetComponent<Transform>()->SetPosition(Vector3(-1.99f, -1.28f, 0.69f));
			mSelectImage[1]->GetComponent<Transform>()->SetPosition(Vector3(-1.73f, -1.28f, 0.69f));
			mSelectImage[2]->GetComponent<Transform>()->SetPosition(Vector3(-1.47f, -1.28f, 0.69f));
			mSelectImage[3]->GetComponent<Transform>()->SetPosition(Vector3(-1.21f, -1.28f, 0.69f));
		}
		else if (mLearnedSkillCount == 5)
		{
			mTransform->SetPosition(Vector3(-1.47f, -1.28f, 0.7f));
			mTransform->SetScale(Vector3(1.37f, 0.3f, 1.f));

			mSelectImage[0]->GetComponent<Transform>()->SetPosition(Vector3(-1.99f, -1.28f, 0.69f));
			mSelectImage[1]->GetComponent<Transform>()->SetPosition(Vector3(-1.73f, -1.28f, 0.69f));
			mSelectImage[2]->GetComponent<Transform>()->SetPosition(Vector3(-1.47f, -1.28f, 0.69f));
			mSelectImage[3]->GetComponent<Transform>()->SetPosition(Vector3(-1.21f, -1.28f, 0.69f));
			mSelectImage[4]->GetComponent<Transform>()->SetPosition(Vector3(-0.95f, -1.28f, 0.69f));
		}
		else if (mLearnedSkillCount == 6)
		{
			mTransform->SetPosition(Vector3(-1.34f, -1.28f, 0.7f));
			mTransform->SetScale(Vector3(1.64f, 0.3f, 1.f));

			mSelectImage[0]->GetComponent<Transform>()->SetPosition(Vector3(-1.99f, -1.28f, 0.69f));
			mSelectImage[1]->GetComponent<Transform>()->SetPosition(Vector3(-1.73f, -1.28f, 0.69f));
			mSelectImage[2]->GetComponent<Transform>()->SetPosition(Vector3(-1.47f, -1.28f, 0.69f));
			mSelectImage[3]->GetComponent<Transform>()->SetPosition(Vector3(-1.21f, -1.28f, 0.69f));
			mSelectImage[4]->GetComponent<Transform>()->SetPosition(Vector3(-0.95f, -1.28f, 0.69f));
			mSelectImage[5]->GetComponent<Transform>()->SetPosition(Vector3(-0.69f, -1.28f, 0.69f));
		}

	}  

	void SkillSelectBox::ImageSetting()  //사용 가능스킬을 스킬이미지에 정보 넘기기
	{
		for (int i = 0; i < 5; i++)
		{
			mSelectImage[i]->SetSkillID(eSkillID::None);
			mSelectImage[i]->SetInSkill(false);
		}

		std::bitset<5> bitset = mTree->GetSkLevelBitSet();
		int count = 0;
		if (bitset[0] == 1)
		{
			count++;
			mSelectImage[0]->SetInSkill(true);
			mSelectImage[0]->SetMaterName(L"FireAuraIconMater");
			mSelectImage[0]->SetTex(Resources::Find<Texture>(L"FireAuraIconTex"));
			mSelectImage[0]->SetMater();
			mSelectImage[0]->SetSkillID(eSkillID::FireAura);
			mSelectImage[0]->SetCoolTime(0.2f);
		}
		if (bitset[1] == 1)
		{
			count++;

			for (int i = 0; i < 5; i++)
			{
				if (mSelectImage[i]->GetSkillID() == eSkillID::None)
				{
					mSelectImage[i]->SetInSkill(true);
					mSelectImage[i]->SetMaterName(L"FireWallMater");
					mSelectImage[i]->SetTex(Resources::Find<Texture>(L"FireWallIconTex"));
					mSelectImage[i]->SetMater();
					mSelectImage[i]->SetSkillID(eSkillID::FireWall);
					mSelectImage[i]->SetCoolTime(0.14f);
					break;
				}
				
			}
		}
		if (bitset[2] == 1)
		{
			count++;

			for (int i = 0; i < 5; i++)
			{
				if (mSelectImage[i]->GetSkillID() == eSkillID::None)
				{
					mSelectImage[i]->SetInSkill(true);
					mSelectImage[i]->SetMaterName(L"MeteorIconMater");
					mSelectImage[i]->SetTex(Resources::Find<Texture>(L"MeteorIconTex"));
					mSelectImage[i]->SetMater();
					mSelectImage[i]->SetSkillID(eSkillID::Meteor);
					mSelectImage[i]->SetCoolTime(0.1f);
					break;
				}
			}
		}
		if (bitset[3] == 1)
		{
			count++;

			for (int i = 0; i < 5; i++)
			{
				if (mSelectImage[i]->GetSkillID() == eSkillID::None)
				{
					mSelectImage[i]->SetInSkill(true);
					mSelectImage[i]->SetMaterName(L"HydraIconMater");
					mSelectImage[i]->SetTex(Resources::Find<Texture>(L"HydraIconTex"));
					mSelectImage[i]->SetMater();
					mSelectImage[i]->SetSkillID(eSkillID::Hydra);
					mSelectImage[i]->SetCoolTime(0.2f);
					break;
				}
			}
		}
		if (bitset[4] == 1)
		{
			count++;

			for (int i = 0; i < 5; i++)
			{
				if (mSelectImage[i]->GetSkillID() == eSkillID::None)
				{
					mSelectImage[i]->SetInSkill(true);
					mSelectImage[i]->SetMaterName(L"TelePortIconMater");
					mSelectImage[i]->SetTex(Resources::Find<Texture>(L"TelePortIconTex"));
					mSelectImage[i]->SetMater();
					mSelectImage[i]->SetSkillID(eSkillID::Teleport);
					mSelectImage[i]->SetCoolTime(0.2f);
					break;
				}
			}
		}
		mLearnedSkillCount = count;
	}

	void SkillSelectBox::SlotClickCheck()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			for (int i = 0; i < 4; i++)
			{
				Vector2 LBpos = mSkillSlot[i]->GetComponent<Transform>()->GetWorldLeftBottom();
				Vector2 RTpos = mSkillSlot[i]->GetComponent<Transform>()->GetWorldRightUp();
				Vector3 cursorPos = Cursor::GetPos() -PlayerScript::GetPlayerPos();

				if (LBpos.x <= cursorPos.x && cursorPos.x <= RTpos.x
					&& LBpos.y <= cursorPos.y && cursorPos.y <= RTpos.y)
				{
					mSelectSlotNum = i;
					mOn = true;
					for (int i = 0; i < 5; i++)
					{
						mSelectImage[i]->SetOnOff(true);
					}
					break;
				}
			}
		}
	}

	void SkillSelectBox::SelectClickCheck()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			for (int i = 0; i < mLearnedSkillCount; i++)
			{
				Vector2 LBpos = mSelectImage[i]->GetComponent<Transform>()->GetWorldLeftBottom();
				Vector2 RTpos = mSelectImage[i]->GetComponent<Transform>()->GetWorldRightUp();
				Vector3 cursorPos = Cursor::GetPos() - PlayerScript::GetPlayerPos();

				if (LBpos.x <= cursorPos.x && cursorPos.x <= RTpos.x
					&& LBpos.y <= cursorPos.y && cursorPos.y <= RTpos.y)
				{
					MeshRenderer* mr = mSkillSlot[mSelectSlotNum]->GetComponent<MeshRenderer>();
					std::shared_ptr<Material> mt = std::make_shared<Material>();
					

					std::shared_ptr<Shader> shader;
					if (mSelectSlotNum == 0)
						shader = Resources::Find<Shader>(L"CoolTimeShader1");
					else if(mSelectSlotNum == 1)
						shader = Resources::Find<Shader>(L"CoolTimeShader2");
					else if (mSelectSlotNum == 2)
						shader = Resources::Find<Shader>(L"CoolTimeShader3");
					else if (mSelectSlotNum == 3)
						shader = Resources::Find<Shader>(L"CoolTimeShader4");
										

					mt->SetShader(shader);
					mt->SetTexture(mSelectImage[i]->GetTex());
					mt->SetRenderingMode(eRenderingMode::Transparent);
					mr->SetMaterial(mt);

					mSkillSlot[mSelectSlotNum]->SetCoolSpeed(mSelectImage[i]->GetCoolTime());
					mSkillSlot[mSelectSlotNum]->SetSkillID(mSelectImage[i]->GetID());

					for (int i = 0; i < 5; i++)
					{
						mSelectImage[i]->SetOnOff(false);
					}

					mOn = false;
					break;
				}
			}
		}
	}

	

	
	


}
