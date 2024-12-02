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

// 플레이어 상태
enum class PlayerState
{
	Idle,	// 대기
	Move,	// 달리기
	DuckDown,	// 숙이기
	DuckDownMove,	// 숙이면서 달리기
	Jump,	// 점프
	Hang,	// 매달리기
	Release,	// 놓기
	Skill,	// 스킬
	AttackNormal,	// 기본 공격
	Hit,	// 피격
	Dead	// 사망
};

// 플레이어 방향
enum Dir
{
	DIR_LEFT,
	DIR_RIGHT,
};

// Sound
enum class SoundType
{
	BGM,
	Normal,
};