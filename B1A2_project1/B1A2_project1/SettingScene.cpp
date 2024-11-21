#include "pch.h"
#include "SettingScene.h"
#include "Panel.h"
#include "Button.h"
#include "ValueManager.h"

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
	// 화면 크기로 설정하기
	GET_SINGLE(ValueManager)->SetWinSize({ ::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN) });
	Vec2Int size = GET_SINGLE(ValueManager)->GetWinSize();
	HWND hwnd = GET_SINGLE(ValueManager)->GetHwnd();

	// 현재 창 스타일 가져오기
	DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
	// 전체화면 스타일로 변환
	::SetWindowLong(hwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
	// 창 크기 재설정
	::SetWindowPos(hwnd, NULL, 0, 0, size.x, size.y, SWP_NOZORDER | SWP_SHOWWINDOW);
}