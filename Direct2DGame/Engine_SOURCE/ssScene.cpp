#include "ssScene.h"
#include "ssSceneManager.h"

namespace ss
{
	Scene::Scene()
	{
		mLayers.resize((int)ss::enums::eLayerType::End);
	}
	Scene::~Scene()
	{

	}

	void Scene::Initialize()
	{
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}

	void Scene::Destroy()
	{
		for (Layer& layer : mLayers)
		{
			layer.Destory();
		}
	}

	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		mLayers[(int)type].AddGameObject(gameObj);

		auto gameObjects = gameObj->GetOtherGameObjects();
		for (auto otherGameObject : gameObjects)
		{
			mLayers[(int)otherGameObject->layerType].AddGameObject(otherGameObject->gameObject);
		}
		
	}
	void Scene::AddGameObjectToActiveScene(eLayerType type, GameObject* gameObj)
	{
		SceneManager::GetActiveScene()->mLayers[(int)type].AddGameObject(gameObj);
	}
}
