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
	LAYER_ITEM,
	LAYER_PLAYER,
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
	CLT_PLAYER,		// 0
	CLT_ITEM,		// 1
	CLT_GROUND,		// 2
	CLT_WALL,		// 3
	CLT_NONE,
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

// Dialogue
enum class DialogueState
{
	Running,
	Wait,
	Hidden,
};

// Item 종류
enum class ItemType
{
	Pencil,
	Match,
	Key,
};

// F_key 
enum class FKeyState
{
	Hidden,
	Show,
};

enum class ItemState
{
	Hidden,
	Show,
};

// Inventory
enum class InventoryState
{
	Hidden,
	Show,
};

// Scene
enum class SceneState
{
	Play,
	Menu,
	Inventory,
};

// Object
enum class ObjectState
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
	Dead,	// 사망
};