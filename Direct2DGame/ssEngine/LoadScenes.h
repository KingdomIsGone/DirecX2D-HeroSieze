#pragma once
#include "..\Engine_SOURCE\ssSceneManager.h"
#include "ssPlayScene.h"
#include "ssUIScene.h"
#include "ssDesertTownScene.h"
#include "ssDesertFieldScene.h"
#include "ssDesertDungeon1.h"
#include "ssDesertDungeon2.h"
#include "ssDesertBossRoom.h"
#include "ssWoodsField.h"
#include "ssValkyrieScene.h"
#include "ssAnubisRoom.h"
#include "ssTitleScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\ssEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\ssEngine.lib")
#endif



//#include "..\ssEngine\\ssPlayScene.h"
//#include "ssSceneManager.h"
namespace ss
{
	void InitializeScenes()
	{
		//SceneManager::CreateScene<DesertFieldScene>(L"DesertFieldScene");
		//SceneManager::CreateScene<DesertDungeon1>(L"DesertDungeon1");
		//SceneManager::CreateScene<WoodsField>(L"WoodsField");
		//SceneManager::CreateScene<DesertTownScene>(L"DesertTownScene");
		//SceneManager::CreateScene<DesertDungeon2>(L"DesertDungeon2");
		//SceneManager::CreateScene<DesertBossRoom>(L"DesertBossRoom");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<UIScene>(L"UIScene");
		SceneManager::CreateScene<AnubisRoom>(L"AnubisRoom");
		SceneManager::CreateScene<ValkyrieScene>(L"ValkyrieScene");
	}
}