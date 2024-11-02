#include "pch.h"
#include "Scene.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Panel.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
	if (_panel != nullptr)
		_panel->BeginPlay();
}

void Scene::Update()
{
	if (_panel != nullptr)
		_panel->Tick();
}

void Scene::Render(HDC hdc)
{
	if (_panel != nullptr)
		_panel->Render(hdc);
}