#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "SettingScene.h"
#include "GameScene.h"
#include "DevScene.h"

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);
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
	case SceneType::TitleScene:
		newScene = new TitleScene();
		break;
	case SceneType::SettingScene:
		newScene = new SettingScene();
		break;
	case SceneType::GameScene:
		newScene = new GameScene();
		break;
	case SceneType::DevScene:
		newScene = new DevScene();
		break;
	}

	SAFE_DELETE(_scene);

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
