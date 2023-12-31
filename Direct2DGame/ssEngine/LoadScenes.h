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
#include "ssEndingScene.h"

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
		//SceneManager::CreateScene<UIScene>(L"UIScene");
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<EndingScene>(L"EndingScene");
		SceneManager::CreateScene<ForestScene>(L"ForestScene");
		SceneManager::CreateScene<ValkyrieScene>(L"ValkyrieScene");
		SceneManager::CreateScene<DesertMap>(L"DesertMap");
		SceneManager::CreateScene<Town>(L"Town");
		SceneManager::CreateScene<AnubisRoom>(L"AnubisRoom");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
	}
}