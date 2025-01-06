#include "pch.h"
#include "ValueManager.h"
#include "SceneManager.h"

void ValueManager::Init(HWND hwnd)
{
	// 윈도우 핸들
	_hwnd = hwnd;

	// 윈도우 창 사이즈
	_winSize.x = DefaultWinSizeX;
	_winSize.y = DefaultWinSizeY;
}

Vec2 ValueManager::GetWinSizeAdjustment()
{
	Vec2 adjustment{
		(float)_winSize.x / (float)DefaultWinSizeX,
		(float)_winSize.y / (float)DefaultWinSizeY
	};
	
	return adjustment;
}

Vec2 ValueManager::GetCameraPosAdjustment()
{
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	Vec2 adjustment{
		cameraPos.x - ((float)_winSize.x / 2),
		cameraPos.y - ((float)_winSize.y / 2)
	};

	return adjustment;
}