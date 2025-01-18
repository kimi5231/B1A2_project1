#include "pch.h"
#include "SettingScene.h"
#include "InputManager.h"
#include "ValueManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SettingPanel.h"

SettingScene::SettingScene()
{
}

SettingScene::~SettingScene()
{
}

void SettingScene::Init()
{
	// ÆÐ³Î
	{
		SettingPanel* ui = new SettingPanel();
		AddPanel(ui);
	}
	
	Super::Init();
}

void SettingScene::Update()
{
	Super::Update();

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Esc))
	{
		GET_SINGLE(SceneManager)->ChangeScene(SceneType::TitleScene);
	}
}

void SettingScene::Render(HDC hdc)
{
	Super::Render(hdc);
}