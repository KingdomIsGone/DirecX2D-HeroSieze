#include "ssPlayer.h"
#include "ssMeshRenderer.h"
#include "ssResources.h"
#include "ssInput.h"
#include "ssCamera.h"
#include "ssAnimator.h"
#include "ssPlayerScript.h"
#include "ssP_HpSmallBar.h"
#include "ssP_HpSmallBarFill.h"
#include "Inventory.h"
#include "ssLight.h"
#include "ssEquipmentSlot.h"
#include "ssItemList.h"
#include "ssItemBackground.h"
#include "ssItemImage.h"

namespace ss
{
	Player::Player()
		: mCurHp(3000.0f)
		, mPrevHp(3000.0f)
	{
		mTransform = GetComponent<Transform>();
		mScript = AddComponent<PlayerScript>();

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		//애니메이션
		{
			SetName(L"Player");
			Collider2D* cd = AddComponent<Collider2D>();
			cd->SetSize(Vector2(0.18f, 0.23f));
			cd->SetCollideType(eCollideType::Player);


			const float pi = 3.141592f;
			float degree = pi / 8.0f;

			GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
			GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.5f, 1.0f));
			//player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));

			//애니메이션 세팅
			MeshRenderer* mr = AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));

			std::shared_ptr<Texture> MoveDownTex
				= Resources::Load<Texture>(L"MoveDownTex", L"..\\Resources\\Texture\\Player\\Move\\MoveDown.png");

			std::shared_ptr<Texture> MoveUpTex
				= Resources::Load<Texture>(L"MoveUpTex", L"..\\Resources\\Texture\\Player\\Move\\MoveUp.png");

			std::shared_ptr<Texture> MoveRightTex
				= Resources::Load<Texture>(L"MoveRightTex", L"..\\Resources\\Texture\\Player\\Move\\MoveRight.png");

			std::shared_ptr<Texture> MoveLeftTex
				= Resources::Load<Texture>(L"MoveLeftTex", L"..\\Resources\\Texture\\Player\\Move\\MoveLeft.png");

			Animator* at = AddComponent<Animator>();
			at->Create(L"MoveDown", MoveDownTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 48.0f), 6);
			at->Create(L"MoveUp", MoveUpTex, Vector2(0.0f, 0.0f), Vector2(32.0f, 48.0f), 6);
			at->Create(L"MoveRight", MoveRightTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);
			at->Create(L"MoveLeft", MoveLeftTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);

			std::shared_ptr<Texture> StandLeftTex
				= Resources::Load<Texture>(L"StandLeftTex", L"..\\Resources\\Texture\\Player\\Stand\\StandLeft.png");

			std::shared_ptr<Texture> StandRightTex
				= Resources::Load<Texture>(L"StandRightTex", L"..\\Resources\\Texture\\Player\\Stand\\StandRight.png");

			std::shared_ptr<Texture> StandDownTex
				= Resources::Load<Texture>(L"StandDownTex", L"..\\Resources\\Texture\\Player\\Stand\\StandDown.png");

			std::shared_ptr<Texture> StandUpTex
				= Resources::Load<Texture>(L"StandUpTex", L"..\\Resources\\Texture\\Player\\Stand\\StandUp.png");

			at->Create(L"StandRight", StandRightTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);
			at->Create(L"StandLeft", StandLeftTex, Vector2(0.0f, 0.0f), Vector2(34.0f, 53.0f), 6);
			at->Create(L"StandDown", StandDownTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 48.0f), 6);
			at->Create(L"StandUp", StandUpTex, Vector2(0.0f, 0.0f), Vector2(31.0f, 48.0f), 6);

			std::shared_ptr<Texture> AttackDownTex
				= Resources::Load<Texture>(L"AttackDownTex", L"..\\Resources\\Texture\\Player\\Attack\\AttackDown.png");
			std::shared_ptr<Texture> AttackUpTex
				= Resources::Load<Texture>(L"AttackUpTex", L"..\\Resources\\Texture\\Player\\Attack\\AttackUp.png");
			std::shared_ptr<Texture> AttackRightTex
				= Resources::Load<Texture>(L"AttackRightTex", L"..\\Resources\\Texture\\Player\\Attack\\AttackRight.png");
			std::shared_ptr<Texture> AttackLeftTex
				= Resources::Load<Texture>(L"AttackLeftTex", L"..\\Resources\\Texture\\Player\\Attack\\AttackLeft.png");

			at->Create(L"AttackDown", AttackDownTex, Vector2(0.0f, 0.0f), Vector2(84.0f, 66.0f), 8
				, Vector2(-0.01f, 0.02f), 0.05f);
			at->Create(L"AttackUp", AttackUpTex, Vector2(0.0f, 0.0f), Vector2(82.0f, 67.0f), 8
				, Vector2(0.01f, 0.08f), 0.05f);
			at->Create(L"AttackRight", AttackRightTex, Vector2(0.0f, 0.0f), Vector2(71.0f, 63.0f), 8
				, Vector2(0.0f, -0.02f), 0.05f);
			at->Create(L"AttackLeft", AttackLeftTex, Vector2(0.0f, 0.0f), Vector2(71.0f, 63.0f), 8
				, Vector2(0.0f, -0.02f), 0.05f);
		}
	
		//hp바, fill
		mSmallHpBar = new P_HpSmallBar();
		mSmallHpBar->SetName(L"PlayerSmallHpBar");
		mTransform = GetComponent<Transform>();
		mSmallHpBar->GetComponent<Transform>()->SetParent(mTransform);
		AddOtherGameObject(mSmallHpBar, eLayerType::MonsterUI);

		mSmallHpBarFill = new P_HpSmallBarFill();
		mSmallHpBarFill->GetComponent<Transform>()->SetParent(mTransform);
		Vector3 tempPos2 = mSmallHpBarFill->GetComponent<Transform>()->GetPosition();
		AddOtherGameObject(mSmallHpBarFill, eLayerType::MonsterUI);

		//라이트
		GameObject* light = new GameObject();
		light->SetName(L"LightInPlayer");
		AddOtherGameObject(light, eLayerType::Light);
		Light* lightComp = light->AddComponent<Light>();
		lightComp->SetType(eLightType::Directional);
		lightComp->SetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));

		//inventory
		{
			//장비슬롯

			//weapon
			EquipmentSlot* WeaponSlot = new EquipmentSlot();
			WeaponSlot->SetMaterialName(L"WeaponSlotMater");
			WeaponSlot->GetComponent<Transform>()->SetScale(0.4f, 0.7f, 1.0f);
			Vector3 WeaponPos = WeaponSlot->GetComponent<Transform>()->GetPosition();
			WeaponPos.x += -2.05f;
			WeaponPos.y += 0.2f;
			WeaponSlot->GetComponent<Transform>()->SetPosition(WeaponPos);
			AddOtherGameObject(WeaponSlot, eLayerType::Inventory);

			ItemBackground* weaponBack = new ItemBackground(nullptr);
			weaponBack->GetComponent<Transform>()->SetScale(0.4f, 0.7f, 1.0f);
			Vector3 WeaponBackPos = WeaponPos;
			WeaponBackPos.z -= 0.01f;
			weaponBack->GetComponent<Transform>()->SetPosition(WeaponBackPos);
			AddOtherGameObject(weaponBack, eLayerType::Inventory);
			WeaponSlot->SetItemBack(weaponBack);

			//Armor
			EquipmentSlot* ArmorSlot = new EquipmentSlot();
			ArmorSlot->SetMaterialName(L"ArmorSlotMater");
			ArmorSlot->GetComponent<Transform>()->SetScale(0.4f, 0.7f, 1.0f);
			Vector3 ArmorPos = ArmorSlot->GetComponent<Transform>()->GetPosition();
			ArmorPos.x += -1.55f;
			ArmorPos.y += 0.26f;
			ArmorSlot->GetComponent<Transform>()->SetPosition(ArmorPos);
			AddOtherGameObject(ArmorSlot, eLayerType::Inventory);

			ItemBackground* ArmorBack = new ItemBackground(nullptr);
			ArmorBack->GetComponent<Transform>()->SetScale(0.4f, 0.7f, 1.0f);
			Vector3 ArmorBackPos = ArmorPos;
			ArmorBackPos.z -= 0.01f;
			ArmorBack->GetComponent<Transform>()->SetPosition(ArmorBackPos);
			AddOtherGameObject(ArmorBack, eLayerType::Inventory);
			ArmorSlot->SetItemBack(ArmorBack);

			//Shield
			EquipmentSlot* ShieldSlot = new EquipmentSlot();
			ShieldSlot->SetMaterialName(L"ShieldSlotMater");
			ShieldSlot->GetComponent<Transform>()->SetScale(0.4f, 0.7f, 1.0f);
			Vector3 ShieldPos = ShieldSlot->GetComponent<Transform>()->GetPosition();
			ShieldPos.x += -1.05f;
			ShieldPos.y += 0.2f;
			ShieldSlot->GetComponent<Transform>()->SetPosition(ShieldPos);
			AddOtherGameObject(ShieldSlot, eLayerType::Inventory);

			ItemBackground* ShieldBack = new ItemBackground(nullptr);
			ShieldBack->GetComponent<Transform>()->SetScale(0.4f, 0.7f, 1.0f);
			Vector3 ShieldBackPos = ShieldPos;
			ShieldBackPos.z -= 0.01f;
			ShieldBack->GetComponent<Transform>()->SetPosition(ShieldBackPos);
			AddOtherGameObject(ShieldBack, eLayerType::Inventory);
			ShieldSlot->SetItemBack(ShieldBack);

			//Helmet
			EquipmentSlot* HelmetSlot = new EquipmentSlot();
			HelmetSlot->SetMaterialName(L"HelmetSlotMater");
			HelmetSlot->GetComponent<Transform>()->SetScale(0.4f, 0.4f, 1.0f);
			Vector3 HelmetPos = HelmetSlot->GetComponent<Transform>()->GetPosition();
			HelmetPos.x += -1.55f;
			HelmetPos.y += 0.85f;
			HelmetSlot->GetComponent<Transform>()->SetPosition(HelmetPos);
			AddOtherGameObject(HelmetSlot, eLayerType::Inventory);

			ItemBackground* HelmetBack = new ItemBackground(nullptr);
			HelmetBack->GetComponent<Transform>()->SetScale(0.4f, 0.4f, 1.0f);
			Vector3 HelmetBackPos = HelmetPos;
			HelmetBackPos.z -= 0.01f;
			HelmetBack->GetComponent<Transform>()->SetPosition(HelmetBackPos);
			AddOtherGameObject(HelmetBack, eLayerType::Inventory);
			HelmetSlot->SetItemBack(HelmetBack);

			//Belt
			EquipmentSlot* BeltSlot = new EquipmentSlot();
			BeltSlot->SetMaterialName(L"BeltSlotMater");
			BeltSlot->GetComponent<Transform>()->SetScale(0.4f, 0.35f, 1.0f);
			Vector3 BeltPos = BeltSlot->GetComponent<Transform>()->GetPosition();
			BeltPos.x += -1.55f;
			BeltPos.y += -0.3f;
			BeltSlot->GetComponent<Transform>()->SetPosition(BeltPos);
			AddOtherGameObject(BeltSlot, eLayerType::Inventory);

			ItemBackground* BeltBack = new ItemBackground(nullptr);
			BeltBack->GetComponent<Transform>()->SetScale(0.4f, 0.35f, 1.0f);
			Vector3 BeltBackPos = BeltPos;
			BeltBackPos.z -= 0.01f;
			BeltBack->GetComponent<Transform>()->SetPosition(BeltBackPos);
			AddOtherGameObject(BeltBack, eLayerType::Inventory);
			BeltSlot->SetItemBack(BeltBack);

			//Shoes
			EquipmentSlot* ShoesSlot = new EquipmentSlot();
			ShoesSlot->SetMaterialName(L"ShoesSlotMater");
			ShoesSlot->GetComponent<Transform>()->SetScale(0.4f, 0.45f, 1.0f);
			Vector3 ShoesPos = ShoesSlot->GetComponent<Transform>()->GetPosition();
			ShoesPos.x += -1.55f;
			ShoesPos.y += -0.76f;
			ShoesSlot->GetComponent<Transform>()->SetPosition(ShoesPos);
			AddOtherGameObject(ShoesSlot, eLayerType::Inventory);

			ItemBackground* ShoesBack = new ItemBackground(nullptr);
			ShoesBack->GetComponent<Transform>()->SetScale(0.4f, 0.45f, 1.0f);
			Vector3 ShoesBackPos = ShoesPos;
			ShoesBackPos.z -= 0.01f;
			ShoesBack->GetComponent<Transform>()->SetPosition(ShoesBackPos);
			AddOtherGameObject(ShoesBack, eLayerType::Inventory);
			ShoesSlot->SetItemBack(ShoesBack);

			//인벤토리
			Inventory* inventory = new Inventory(this);
			inventory->SetName(L"Inventory");
			AddOtherGameObject(inventory, eLayerType::Inventory);
			mScript->SetInventory(inventory);
			inventory->SetLight(lightComp);
			inventory->PushBackEquipSlot(WeaponSlot);
			inventory->PushBackEquipSlot(ArmorSlot);
			inventory->PushBackEquipSlot(ShieldSlot);
			inventory->PushBackEquipSlot(HelmetSlot);
			inventory->PushBackEquipSlot(BeltSlot);
			inventory->PushBackEquipSlot(ShoesSlot);

			/*ItemList* list1 = new ItemList();
			list1->GetComponent<Transform>()->SetScale(0.4f, 0.45f, 1.0f);
			Vector3 List1Pos = list1->GetComponent<Transform>()->GetPosition();
			List1Pos.x += -0.55f;
			List1Pos.y += -0.76f;
			list1->GetComponent<Transform>()->SetPosition(List1Pos);
			AddOtherGameObject(list1, eLayerType::Inventory);*/
		}

	}

	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();

		DamageCheck();
		mCurHp = mScript->GetHp();
		if (mCurHp != mPrevHp)
		{
			mSmallHpBarFill->ChangeHP(mCurHp);

			mPrevHp = mCurHp;
		}

		Vector3 pos = mTransform->GetPosition();

	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}

	void Player::DamageCheck()
	{
		float value = GetChangeHpValue();
		if (value != 0)
		{
			mCurHp += value;
			SetChangeHpValue(0.f);
		}
	}

}