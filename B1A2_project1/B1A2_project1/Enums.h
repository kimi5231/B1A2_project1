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
	CLT_MONSTER,	// 1

	CLT_ITEM,		// 2
	
	CLT_GROUND,		// 3
	CLT_WALL,		// 4
	CLT_SAVE_POINT,	// 5
	CLT_GAME_OVER,	// 6

	CLT_DETECT,		// 7
	CLT_MONSTER_ATTACK,	// 8
	CLT_PLAYER_ATTACK,	// 9 

	CLT_NONE,		
};

// 플레이어 방향
enum Dir
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
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

enum class DialogueType
{
	Bubble,
	CutScene,
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
	CloseAttack,	// 기본 공격
	LongAttack,
	Thrust,		// 찌르기
	BackStep,	// 백스텝
	SlashWave,	// 검기 날리기
	Skill,	// 스킬
	Hang,	// 매달리기
	Release,	// 놓기
	Hit,	// 피격
	Dead,	// 사망
	Chase,	// 추적
	Roaming,	// 배회
	Dash,	// 대쉬
	Return,		// 복귀
};