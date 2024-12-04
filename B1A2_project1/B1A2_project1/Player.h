#pragma once
#include "FlipbookActor.h"
#include <fstream>
#include <iostream>
#include <string>

class Flipbook;
class BoxCollider;

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

struct PlayerStat
{
	int32 healthPoint = 0;
	int32 runSpeed = 0;
	int32 crouchSpeed = 0;
	int32 jumpHeight = 0;
	bool enemyExistInAttRange = false;
	int32 attRange = 0;
	int32 attStepDistance = 0;
	int32 attDamage = 0;
	int32 skillDamage = 0;
	int32 skillRange = 0;
	int32 skillDuration = 0;
	int32 skillStepDistance = 0;

	void LoadFile(const std::wstring& path)
	{
		std::ifstream ifs;
		ifs.open(path);

		std::string line;

		if (std::getline(ifs, line))
		{
			std::istringstream lineStream(line);
			std::string cell;
			int column = 0;

			while (std::getline(lineStream, cell, ','))
			{
				switch (column)
				{
				case 0: this->healthPoint = std::stoi(cell); break;
				case 1: this->runSpeed = std::stoi(cell); break;
				case 2: this->crouchSpeed = std::stoi(cell); break;
				case 3: this->jumpHeight = std::stoi(cell); break;
				case 4: this->enemyExistInAttRange = std::stoi(cell); break;
				case 5: 
					if (cell == "1")
						this->attRange = true; 
					break;
				case 6: this->attStepDistance = std::stoi(cell); break;
				case 7: this->attDamage = std::stoi(cell); break;
				case 8: this->skillDamage = std::stoi(cell); break;
				case 9: this->skillRange = std::stoi(cell); break;
				case 10: this->skillDuration = std::stoi(cell); break;
				case 11: this->skillStepDistance = std::stoi(cell); break;
				}
				++column;
			}
		}
		ifs.close();
	}
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

public:
	// Player Stat
	PlayerStat* GetPlayerStat() { return _playerStat; }
	void SetPlayerStat(PlayerStat* playerStat) { _playerStat = playerStat; }

	// 현실에서의 단위를 픽셀 단위로 바꿈
	void CalPixelPerSecond();

public:
	// Player State
	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickDuckDown();
	virtual void TickDuckDownMove();
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

public: 
	// Collider
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);
	
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);	// 튕기기
	void TickGravity();

private:
	// 마지 리소스
	Flipbook* _flipbookPlayerIdle[2] = {};
	Flipbook* _flipbookPlayerMove[2] = {};
	Flipbook* _flipbookPlayerDuckDown[2] = {};
	Flipbook* _flipbookPlayerDuckDownMove[2] = {};
	Flipbook* _flipbookPlayerJump[2] = {};
	Flipbook* _flipbookPlayerHang[2] = {};
	Flipbook* _flipbookPlayerRelease[2] = {};
	Flipbook* _flipbookPlayerSkill[2] = {};
	Flipbook* _flipbookPlayerAttackNormal[2] = {};
	Flipbook* _flipbookPlayerHit[2] = {};
	Flipbook* _flipbookPlayerDead[2] = {};

private:
	Vec2Int _cellPos = {};
	Dir _dir = DIR_RIGHT;
	PlayerState _state = PlayerState::Idle;
	bool _keyPressed = false;
	PlayerStat* _playerStat = {};

	int32 _geravity = 1000;
};

