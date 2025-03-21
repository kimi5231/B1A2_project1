#pragma once
#include "Monster.h"

struct TiredOfficeWorkerStat
{
	int32 id;	// A
	int32 hp;	// B
	float healtemDropRate;	// C
	float speed;	// D
	float chaseSpeed;	// E
	Vec2Int playerDetection;	// F, G
	int32 knockBackDistance; // H
	int32 attackRange;	// I
	int32 attack;	// J
	float idleTime;	// K

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
				case 0:this->id = std::stoi(cell); break;	// A
				case 1: this->hp = std::stoi(cell); break;	// B
				case 2: this->healtemDropRate = std::stof(cell); break;	// C
				case 3: this->speed = std::stof(cell); break;	// D
				case 4: this->chaseSpeed = std::stof(cell); break;	// E
				case 5: this->playerDetection.x = std::stoi(cell); break;	// F
				case 6: this->playerDetection.y = std::stoi(cell); break;	// G
				case 7: this->knockBackDistance = std::stoi(cell); break;	// H
				case 8: this->attackRange = std::stoi(cell); break;	// I
				case 9: this->attack = std::stoi(cell); break;	// J
				case 10: this->idleTime = std::stof(cell); break;	// K
				}
				++column;
			}
		}
		ifs.close();
	}
};

class TiredOfficeWorker : public Monster
{
	using Super = Monster;
public:
	TiredOfficeWorker();
	virtual ~TiredOfficeWorker() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void TickIdle() override;
	virtual void TickCloseAttack() override;
	virtual void TickHit() override;
	virtual void TickDead() override;
	virtual void TickChase() override;
	virtual void TickRoaming() override;
	virtual void UpdateAnimation() override;

public:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

private:
	void CalPixelPerSecond();

private:
	// Flipbook
	Flipbook* _flipbookIdle[2] = {};
	Flipbook* _flipbookNormalAttack[2] = {};
	Flipbook* _flipbookHit[2] = {};
	Flipbook* _flipbookDead[2] = {};
	Flipbook* _flipbookChase[2] = {};
	Flipbook* _flipbookRoaming[2] = {};

private:
	TiredOfficeWorkerStat* _stat;
	float _moveDistance;
	float _currentMoveDistance;
	float _sumTime = 0.f;
};