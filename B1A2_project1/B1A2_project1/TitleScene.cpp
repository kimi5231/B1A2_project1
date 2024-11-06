#include "pch.h"
#include "TitleScene.h"
#include "Panel.h"
#include "Button.h"
#include "UI.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	Super::Init();

	_panel = new Panel();

	// Title 추가
	// 일단은 위치 확인을 위해 Button으로 생성 => 추후 변경 예정
	{
		Button* title = new Button();
		title->SetPos({ 350, 250 });
		title->SetSize({ 545, 339 });
		_panel->AddChild(title);
	}
	
	// 게임 시작 Button 추가
	{
		Button* button = new Button();
		button->SetPos({ 1100, 400 });
		button->SetSize({ 163, 60 });
		button->AddOnClickDelegate(this, &TitleScene::OnClickStartButton);
		_panel->AddChild(button);
	}

	// 설정 Button 추가
	{
		Button* button = new Button();
		button->SetPos({ 1100, 500 });
		button->SetSize({ 163, 60 });
		button->AddOnClickDelegate(this, &TitleScene::OnClickSettingButton);
		_panel->AddChild(button);
	}

	// 게임 종료 Button 추가
	{
		Button* button = new Button();
		button->SetPos({ 1100, 600 });
		button->SetSize({ 163, 60 });
		button->AddOnClickDelegate(this, &TitleScene::OnClickEndButton);
		_panel->AddChild(button);
	}
}

void TitleScene::Update()
{
	Super::Update();
}

void TitleScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

void TitleScene::OnClickStartButton()
{
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::DevScene);
}

void TitleScene::OnClickSettingButton()
{
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::SettingScene);
}

void TitleScene::OnClickEndButton()
{
	// 추후 게임을 종료할 것인지 물어보는 메세지 창을 추가할 예정.
	// 일단은 바로 종료되게 설정.
	::PostQuitMessage(0);
}