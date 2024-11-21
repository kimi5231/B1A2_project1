#include "pch.h"
#include "ValueManager.h"

void ValueManager::Init(HWND hwnd)
{
	// 윈도우 핸들
	_hwnd = hwnd;

	// 윈도우 창 크기
	_winSize.x = 1280;
	_winSize.y = 720;


}

void ValueManager::Update()
{
}