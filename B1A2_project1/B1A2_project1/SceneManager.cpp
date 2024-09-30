#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"

void SceneManager::Init()
{
}

void SceneManager::Update()
{
}

void SceneManager::Render(HDC hdc)
{
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
		return;

	// 货肺款 Scene 积己
	Scene* newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::DevScene:
		newScene = new DevScene();
		break;
	//case SceneType::GameScene:
	//	newScene = new GameScene();
	//	break;
	}

	SAFE_DELETE(_scene);

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
