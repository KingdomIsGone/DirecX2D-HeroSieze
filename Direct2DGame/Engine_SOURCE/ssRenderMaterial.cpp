#include "ssRenderMaterial.h"
#include "ssTexture.h"
#include "ssResources.h"
#include "ssMaterial.h"

namespace ss
{
	void RenderMaterial::MaterialSetting()
	{
		std::shared_ptr<Shader> shader
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

		//MapDot
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"MapDotTex", L"..\\Resources\\Texture\\UI\\MapDot.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(shader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"MapDot", spriteMateiral);
		}
		//MapFrame
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"MapFrameTex", L"..\\Resources\\Texture\\UI\\MapFrame.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(shader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"MapFrameMater", spriteMateiral);
		}

		//헤드
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"head", L"..\\Resources\\Texture\\Player\\head.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(shader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"PyroHead", spriteMateiral);
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

		//mpBar
		{
			std::shared_ptr<Texture> MpBarTex
				= Resources::Load<Texture>(L"MpBarTex", L"..\\Resources\\Texture\\UI\\BlueBar.png");
			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(SpShader);
			spriteMateiral->SetTexture(MpBarTex);
			spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"MpBarMater", spriteMateiral);
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

		std::shared_ptr<Shader> CoolTimeShader1 = Resources::Find<Shader>(L"CoolTimeShader1");
		std::shared_ptr<Shader> CoolTimeShader2 = Resources::Find<Shader>(L"CoolTimeShader2");
		std::shared_ptr<Shader> CoolTimeShader3 = Resources::Find<Shader>(L"CoolTimeShader3");
		std::shared_ptr<Shader> CoolTimeShader4 = Resources::Find<Shader>(L"CoolTimeShader4");
		//스킬 아이콘 메테오
		{
			std::shared_ptr<Texture> MeteorIconTex
				= Resources::Load<Texture>(L"MeteorIconTex", L"..\\Resources\\Texture\\Skill\\Icon\\MeteorIcon.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(CoolTimeShader1);
			spriteMaterial->SetTexture(MeteorIconTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"MeteorIconMater", spriteMaterial);
		}
		//스킬 아이콘 메테오black
		{
			std::shared_ptr<Texture> MeteorIconBlackTex
				= Resources::Load<Texture>(L"MeteorIconBlackTex", L"..\\Resources\\Texture\\Skill\\Icon\\MeteorIconBlack.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(CoolTimeShader1);
			spriteMaterial->SetTexture(MeteorIconBlackTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"MeteorIconBlackMater", spriteMaterial);
		}
		//스킬 아이콘 파이어월
		{
			std::shared_ptr<Texture> FireWallIconTex
				= Resources::Load<Texture>(L"FireWallIconTex", L"..\\Resources\\Texture\\Skill\\Icon\\FireWallIcon.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(CoolTimeShader2);
			spriteMaterial->SetTexture(FireWallIconTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"FireWallMater", spriteMaterial);
		}
		//스킬 아이콘 파이어월black
		{
			std::shared_ptr<Texture> FireWallIconBlackTex
				= Resources::Load<Texture>(L"FireWallIconBlackTex", L"..\\Resources\\Texture\\Skill\\Icon\\FireWallIconBlack.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(CoolTimeShader2);
			spriteMaterial->SetTexture(FireWallIconBlackTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"FireWallIconBlackMater", spriteMaterial);
		}

		//스킬 icon FireAura
		{
			std::shared_ptr<Texture>FireAuraIconTex
				= Resources::Load<Texture>(L"FireAuraIconTex", L"..\\Resources\\Texture\\Skill\\Icon\\FireAuraIcon.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(CoolTimeShader3);
			spriteMaterial->SetTexture(FireAuraIconTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"FireAuraIconMater", spriteMaterial);
		}
		//스킬 icon FireAuraBlack
		{
			std::shared_ptr<Texture>FireAuraIconBlackTex
				= Resources::Load<Texture>(L"FireAuraIconBlackTex", L"..\\Resources\\Texture\\Skill\\Icon\\FireAuraIconBlack.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(CoolTimeShader3);
			spriteMaterial->SetTexture(FireAuraIconBlackTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"FireAuraIconBlackMater", spriteMaterial);
		}
		//스킬 icon Hydra
		{
			std::shared_ptr<Texture>HydraIconTex
				= Resources::Load<Texture>(L"HydraIconTex", L"..\\Resources\\Texture\\Skill\\Icon\\HydraIcon.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(CoolTimeShader4);
			spriteMaterial->SetTexture(HydraIconTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"HydraIconMater", spriteMaterial);
		}
		//스킬 icon Hydra Black
		{
			std::shared_ptr<Texture>HydraIconBlackTex
				= Resources::Load<Texture>(L"HydraIconBlackTex", L"..\\Resources\\Texture\\Skill\\Icon\\HydraIconBlack.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(CoolTimeShader4);
			spriteMaterial->SetTexture(HydraIconBlackTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"HydraIconBlackMater", spriteMaterial);
		}

		//인벤토리
		{
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

			//EquipSelectIndicator
			{
				std::shared_ptr<Texture> EquipSelectTex
					= Resources::Load<Texture>(L"EquipSelectTex", L"..\\Resources\\Texture\\Inventory\\EquipSelect.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(EquipSelectTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"EquipSelectMater", spriteMaterial);
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

			//inventoryItemListSelectEffect
			{
				std::shared_ptr<Texture> ItemListSelectEffectTex
					= Resources::Load<Texture>(L"ItemListSelectEffectTex", L"..\\Resources\\Texture\\Inventory\\Inventory_List_Chosen_spr_0.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(ItemListSelectEffectTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"ItemListSelectEffectMater", spriteMaterial);
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

		//item
		{
			//legendStaff1
			{
				std::shared_ptr<Texture> LegendStaff1Tex
					= Resources::Load<Texture>(L"LegendStaff1Tex", L"..\\Resources\\Texture\\Item\\LegendStaff1.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(LegendStaff1Tex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"LegendStaff1Mater", spriteMaterial);
			}

			//MagicStaff
			{
				std::shared_ptr<Texture> MagicStaffTex
					= Resources::Load<Texture>(L"MagicStaffTex", L"..\\Resources\\Texture\\Item\\MagicStaff.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(MagicStaffTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"MagicStaffMater", spriteMaterial);
			}

			//NormalStaff
			{
				std::shared_ptr<Texture> NormalStaffTex
					= Resources::Load<Texture>(L"NormalStaffTex", L"..\\Resources\\Texture\\Item\\NormalStaff.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(NormalStaffTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"NormalStaffMater", spriteMaterial);
			}

			//MagicHat
			{
				std::shared_ptr<Texture> MagicHatTex
					= Resources::Load<Texture>(L"MagicHatTex", L"..\\Resources\\Texture\\Item\\MagicHat.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(MagicHatTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"MagicHatMater", spriteMaterial);
			}

			//NormalHat
			{
				std::shared_ptr<Texture> NormalHatTex
					= Resources::Load<Texture>(L"NormalHatTex", L"..\\Resources\\Texture\\Item\\NormalHat.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(NormalHatTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"NormalHatMater", spriteMaterial);
			}

			//NormalBoots
			{
				std::shared_ptr<Texture> NormalBootsTex
					= Resources::Load<Texture>(L"NormalBootsTex", L"..\\Resources\\Texture\\Item\\NormalBoots.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(NormalBootsTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"NormalBootsMater", spriteMaterial);
			}

			//LegendBoots
			{
				std::shared_ptr<Texture> LegendBootsTex
					= Resources::Load<Texture>(L"LegendBootsTex", L"..\\Resources\\Texture\\Item\\LegendBoots.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(LegendBootsTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"LegendBootsMater", spriteMaterial);
			}

			//NormalRobe
			{
				std::shared_ptr<Texture> NormalRobeTex
					= Resources::Load<Texture>(L"NormalRobeTex", L"..\\Resources\\Texture\\Item\\NormalRobe.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(NormalRobeTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"NormalRobeMater", spriteMaterial);
			}

			//MagicRobe
			{
				std::shared_ptr<Texture> MagicRobeTex
					= Resources::Load<Texture>(L"MagicRobeTex", L"..\\Resources\\Texture\\Item\\MagicRobe.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(MagicRobeTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"MagicRobeMater", spriteMaterial);
			}

			//NormalBelt
			{
				std::shared_ptr<Texture> NormalBeltTex
					= Resources::Load<Texture>(L"NormalBeltTex", L"..\\Resources\\Texture\\Item\\NormalBelt.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetShader(SpShader);
				spriteMaterial->SetTexture(NormalBeltTex);
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"NormalBeltMater", spriteMaterial);
			}

		}

		//testAlphaPng
		{
			std::shared_ptr<Texture> TestAlphaTex
				= Resources::Load<Texture>(L"TestAlphaTex", L"..\\Resources\\Texture\\test2.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(TestAlphaTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"TestAlphaMater", spriteMaterial);
		}

		//start Button0
		{
			std::shared_ptr<Texture> StartBtn0Tex
				= Resources::Load<Texture>(L"StartBtn0Tex"
					, L"..\\Resources\\Texture\\TitleMenu\\Menu_Button_spr\\Menu_Button_spr_0.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(StartBtn0Tex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"StartBtn0Mater", spriteMaterial);
		}
		//start Button1
		{
			std::shared_ptr<Texture> StartBtn1Tex
				= Resources::Load<Texture>(L"StartBtn1Tex"
					, L"..\\Resources\\Texture\\TitleMenu\\Menu_Button_spr\\Menu_Button_spr_1.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(StartBtn1Tex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"StartBtn1Mater", spriteMaterial);
		}
		//EndingBack
		{
			std::shared_ptr<Texture> EndingTex
				= Resources::Load<Texture>(L"EndingTex"
					, L"..\\Resources\\Texture\\endingScene.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(EndingTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"EndingMater", spriteMaterial);
		}
		std::shared_ptr<Shader> fixedAlphaShader
			= Resources::Find<Shader>(L"FixedAlphaShader");
		//Dim
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Dim", L"..\\Resources\\Texture\\UI\\Dim.png");
				std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
				spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
				spriteMaterial->SetShader(fixedAlphaShader);
				spriteMaterial->SetTexture(texture);
				Resources::Insert(L"DimMater", spriteMaterial);
			}
		}

		//ResourceIcon
		{
			std::shared_ptr<Texture>goldIconTex
				= Resources::Load<Texture>(L"goldIconTex", L"..\\Resources\\Texture\\UI\\MoneySymbol.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(goldIconTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"goldIconMater", spriteMaterial);
		}
		{
			std::shared_ptr<Texture>silverKeyIconTex
				= Resources::Load<Texture>(L"silverKeyIconTex", L"..\\Resources\\Texture\\UI\\Hud_Key_spr.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(silverKeyIconTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"silverKeyIconMater", spriteMaterial);
		}
		{
			std::shared_ptr<Texture>criKeyIconTex
				= Resources::Load<Texture>(L"criKeyIconTex", L"..\\Resources\\Texture\\UI\\Hud_Crystal_Key_spr.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(criKeyIconTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"criKeyIconMater", spriteMaterial);
		}
		{
			std::shared_ptr<Texture>rubyKeyIconTex
				= Resources::Load<Texture>(L"rubyKeyIconTex", L"..\\Resources\\Texture\\UI\\ruby.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(rubyKeyIconTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"rubyKeyIconMater", spriteMaterial);
		}
		{
			std::shared_ptr<Texture>SkillBoxTex
				= Resources::Load<Texture>(L"SkillBoxTex", L"..\\Resources\\Texture\\UI\\SkillSelectBox.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(SkillBoxTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"SkillBoxMater", spriteMaterial);
		}
		{
			std::shared_ptr<Texture>SkillTreeTex
				= Resources::Load<Texture>(L"SkillTreeTex", L"..\\Resources\\Texture\\UI\\Skill_Tree_spr_0.png");
			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(SpShader);
			spriteMaterial->SetTexture(SkillTreeTex);
			spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"SkillTreeMater", spriteMaterial);
		}
	}
}
