#pragma once
#include "FlipbookActor.h"
#include <fstream>
#include <iostream>
#include <string>

class Flipbook;
class BoxCollider;
class ItemActor;

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
	int32 PlayerID = 0;	// A
	int32 healthPoint = 0;	// B
	float runSpeed = 0;	// C
	float crouchSpeed = 0;	// D
	float jumpSpeed = 0;	// E
	int32 skillPoint = 0;	// F
	int32 nAtkRange = 0;	// G
	int32 nLongAtkDistance = 0;	// H
	int32 knockBackDistance = 0;	// I
	float strongAtkMultiplier = 0.f;	// J	
	int32 nAtkDamage = 0;	// K
	int32 skillDamage = 0;	// L
	int32 skillRange = 0;	// M
	float skillDuration = 0;	// N
	int32 skillStepDistance = 0;	// O

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
				case 0:this->PlayerID = std::stoi(cell); break;	// A
				case 1: this->healthPoint = std::stoi(cell); break;	// B
				case 2: this->runSpeed = std::stof(cell); break;	// C
				case 3: this->crouchSpeed = std::stof(cell); break;	// D
				case 4: this->jumpSpeed = std::stof(cell); break;	// E
				case 5: this->skillPoint = std::stoi(cell); break;	// F
				case 6: this->nAtkRange = std::stoi(cell); break;	// G
				case 7: this->nLongAtkDistance = std::stoi(cell); break;	// H
				case 8: this->knockBackDistance = std::stoi(cell); break;	// I
				case 9: this->strongAtkMultiplier = std::stof(cell); break;	// J
				case 10: this->nAtkDamage = std::stoi(cell); break;	// K
				case 11: this->skillDamage = std::stoi(cell); break;	// L
				case 12: this->skillRange = std::stoi(cell); break;	// M
				case 13: this->skillDamage = std::stof(cell); break;	// N
				case 14: this->skillStepDistance = std::stoi(cell); break;	// O
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
	void CalPixelPerSecond();	// 현실에서의 단위를 픽셀 단위로 바꿈

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

public:
	// Item
	void RemoveItem(int32 id, int32 count);
	std::unordered_map<int32, int32>& GetAquireItems() { return _acquiredItems; }

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
	Dir _dir = DIR_RIGHT;
	PlayerState _state;
	bool _keyPressed = false;
	PlayerStat* _playerStat = {};

	// Jump
	int32 _groundCollisionCount = 0;	// 충돌중인 타일맵 개수 (0개일 때 _Ground = true)
	int32 _gravity = 1000;
	float _ySpeed = {};

	bool _isGround = false;
	bool _isAir = false;

	// 획득한 아이템
	ItemActor* _collideItem = {};	// unordered map에 저장하기 위해, 충돌한 아이템을 담을 변수
	std::unordered_map<int32, int32> _acquiredItems;		// [아이템 ID, 개수]
};

