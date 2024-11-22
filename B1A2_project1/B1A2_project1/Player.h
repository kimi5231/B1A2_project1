#pragma once
#include "FlipbookActor.h"

class Flipbook;

enum class PlayerState
{
	Idle,	// 대기
	Move,	// 달리기
	DuckDown,	// 숙이기
	Jump,	// 점프
	Hang,	// 매달리기
	Release,	// 놓기
	Skill,	// 스킬
	AttackNormal,	// 기본 공격
	Hit,	// 피격
	Dead	// 사망
};

class Player : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	// Player State
	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickDuckDown();
	virtual void TickJump();
	virtual void TickHang();
	virtual void TickRelease();
	virtual void TickSkill();
	virtual void TickAttackNormal();
	virtual void TickHit();
	virtual void TickDead();


	void SetState(PlayerState);
	void SetDir(Dir dir);

	void UpdateAnimation();

	// * 목적지 관련 코드 추가 필요

private:
	// 마지 리소스
	Flipbook* _flipbookPlayerIdle[2] = {};
	Flipbook* _flipbookPlayerMove[2] = {};
	Flipbook* _flipbookPlayerDuckDown[2] = {};
	Flipbook* _flipbookPlayerJump[2] = {};
	Flipbook* _flipbookPlayerHang[2] = {};
	Flipbook* _flipbookPlayerRelease[2] = {};
	Flipbook* _flipbookPlayerSkill[2] = {};
	Flipbook* _flipbookPlayerAttackNormal[2] = {};
	Flipbook* _flipbookPlayerHit[2] = {};
	Flipbook* _flipbookPlayer[2] = {};

	Vec2Int _cellPos = {};
	Vec2 _speed = {};
	Dir _dir = DIR_RIGHT;
	PlayerState _state = PlayerState::Idle;
	bool _keyPressed = false;
};

