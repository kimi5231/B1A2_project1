#pragma once
#include "Monster.h"

struct BrokenCopyMachineStat
{
	int32 id;	// A
	int32 hp;	// B
	float healtemDropRate;	// C
	int32 attackRange;	// D
	float projectileSpeed;	// E
	int32 projectileAttack;	// F
	int32 projectileCount;	// G
	float attackCoolTime;	// H

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
				case 3: this->attackRange = std::stoi(cell); break;	// D
				case 4: this->projectileSpeed = std::stof(cell); break;	// E
				case 5: this->projectileAttack = std::stoi(cell); break;	// F
				case 6: this->projectileCount = std::stoi(cell); break;	// G
				case 7: this->attackCoolTime = std::stof(cell); break;	// H
				}
				++column;
			}
		}
		ifs.close();
	}
};

class BrokenCopyMachine : public Monster
{
	using Super = Monster;
public:
	BrokenCopyMachine();
	virtual ~BrokenCopyMachine() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void TickIdle() override;
	virtual void TickLongAttack() override;
	virtual void TickHit() override;
	virtual void TickDead() override;
	virtual void UpdateAnimation() override;

public:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	virtual int32 GetAttack() override;
	virtual int32& GetHp() override { return _stat->hp; }
	virtual Vec2Int GetPlayerDetection() { return {0, 0}; };

private:
	void CalPixelPerSecond();

	void CreateProjectile();

private:
	// Flipbook
	Flipbook* _flipbookIdle[2] = {};
	Flipbook* _flipbookNormalAttack[2] = {};
	Flipbook* _flipbookHit[2] = {};
	Flipbook* _flipbookDead[2] = {};

private:
	BrokenCopyMachineStat* _stat;

	int32 _currentProjectileCount = 0;
	float _sumTime = 0.f;
};