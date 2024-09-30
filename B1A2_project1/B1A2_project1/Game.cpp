#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"

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

	// 더블 버퍼링 코드
	//::GetClientRect(hwnd, &_rect);

	//hdcBack = ::CreateCompatibleDC(_hdc);	// hdc와 호환되는 DC 생성
	//_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);	// hdc와 호환되는 비트맵 생성
	//HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack);	// DC와 BMP 연결
	//::DeleteObject(prev);

	// 각 매니저들 Init
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(TimeManager)->Init();
}

void Game::Update()
{
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(TimeManager)->Update();
}

void Game::Render()
{
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		std::wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_hdc, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		std::wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		::TextOut(_hdc, 550, 10, str.c_str(), static_cast<int32>(str.size()));
	}
}
