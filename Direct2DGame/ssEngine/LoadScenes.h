#pragma once
#include "..\Engine_SOURCE\ssSceneManager.h"
#include "ssPlayScene.h"
#include "ssUIScene.h"

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
		//PlayScene* playScene = new PlayScene();
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<UIScene>(L"UIScene");
	}
}