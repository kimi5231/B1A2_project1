#pragma once

enum class SceneType
{
	None,
	TitleScene,	// 타이틀 씬
	SettingScene, // 설정 씬
	GameScene,	// 인게임 씬
	DevScene,	// 개발 씬
	TilemapScene,
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_TILEMAP,
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

// 충돌
enum class ColliderType
{
	Box,
	Sphere,
};

enum COLLISION_LAYER_TYPE : uint8
{
	CLT_OBJECT,		// 0
	CLT_GROUND,		// 1
	CLT_WALL,		// 2
};

// 플레이어 방향
enum Dir
{
	DIR_LEFT,
	DIR_RIGHT,
};