#pragma once
#include "..\Engine_SOURCE\ssSceneManager.h"
#include "ssPlayScene.h"
#include "ssUIScene.h"
#include "ssValkyrieScene.h"
#include "ssAnubisRoom.h"
#include "ssTitleScene.h"
#include "ssDesertMap.h"
#include "ssTown.h"
#include "ssForestScene.h"

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
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<UIScene>(L"UIScene");
		SceneManager::CreateScene<DesertMap>(L"DesertMap");
		SceneManager::CreateScene<ValkyrieScene>(L"ValkyrieScene");
		SceneManager::CreateScene<Town>(L"Town");
		SceneManager::CreateScene<ForestScene>(L"ForestScene");
		SceneManager::CreateScene<AnubisRoom>(L"AnubisRoom");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
	}
}