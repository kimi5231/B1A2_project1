#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);	// hwnd로 hdc 알 수 있는 함수

	// 상대 경로 path 알아내는 코드
	_resourcePath = std::filesystem::current_path().relative_path();
	std::filesystem::path _resourcePath = std::filesystem::current_path().parent_path().parent_path() / "B1A2_project1\\Resources";
	
	// 더블 버퍼링 코드
	::GetClientRect(hwnd, &_rect);

	hdcBack = ::CreateCompatibleDC(_hdc);	// hdc와 호환되는 DC 생성
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);	// hdc와 호환되는 비트맵 생성
	HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack);	// DC와 BMP 연결
	::DeleteObject(prev);

	// 각 매니저들 Init
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init(hwnd, _resourcePath);

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::TestScene);
}

void Game::Update()
{
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(SceneManager)->Update();
}

void Game::Render()
{
	GET_SINGLE(SceneManager)->Render(hdcBack);

	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		std::wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		std::wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		::TextOut(hdcBack, 550, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	// Double Buffering
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, hdcBack, 0, 0, SRCCOPY); // 비트 블릿 : 고속 복사
	::PatBlt(hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
