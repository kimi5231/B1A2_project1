#include "pch.h"
#include "Game.h"
#include "InputManager.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	hdcBack = ::CreateCompatibleDC(hdc);	// hdc와 호환되는 DC 생성
	_bmpBack = ::CreateCompatibleBitmap(hdc, _rect.right, _rect.bottom);	// hdc와 호환되는 비트맵 생성
	HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack);	// DC와 BMP 연결
	::DeleteObject(prev);

	// 각 매니저들 Init
	GET_SINGLE(InputManager)->Init(hwnd);
}

void Game::Update()
{
	GET_SINGLE(InputManager)->Update();
}

void Game::Render()
{
}
