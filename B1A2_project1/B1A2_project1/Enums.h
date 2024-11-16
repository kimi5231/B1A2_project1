#pragma once

enum class SceneType
{
	None,
	TitleScene,	// 타이틀 씬
	SettingScene, // 설정 씬
	GameScene,	// 인게임 씬
	DevScene,	// 개발 씬
	TestScene,
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_OBJECT,
	LAYER_UI,

	LAYER_MAXCOUNT
};

// 윈도우 창 크기
enum class WinSize
{
	HD,		// 1280*720(Default)
	FullScreen,
};