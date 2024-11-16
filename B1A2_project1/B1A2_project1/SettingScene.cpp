#include "pch.h"
#include "SettingScene.h"
#include "Panel.h"
#include "Button.h"

SettingScene::SettingScene()
{
}

SettingScene::~SettingScene()
{
}

void SettingScene::Init()
{
	// 패널
	{
		Panel* ui = new Panel();
		_panel = ui;
	}
	
	// FullScreen 테스트용 버튼
	{
		Button* ui = new Button();
		ui->SetPos({500, 500});
		ui->SetSize({ 100, 100 });
		ui->AddOnClickDelegate(this, &SettingScene::ChangeFullScreen);
		_panel->AddChild(ui);
	}

	Super::Init();
}

void SettingScene::Update()
{
	Super::Update();
}

void SettingScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

// callback 함수
void SettingScene::ChangeFullScreen()
{

}