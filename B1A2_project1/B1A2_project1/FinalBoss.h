#pragma once
#include "Monster.h"
#include "Player.h"

enum class BehaviorState;
class Node;

struct FinalBossStat
{
	CommonStat commonStat;	// A, B
	float healItemDropRate;	// C
	float speed;	//D
	int32 knockBackDistance;	// E
	int32 backStepDistance;	//F
	float dashSpeed;	// G
	int32 dashDistance;	// H
	int32 closeAtkRange;	// I
	int32 closeAtkDamage;	// J
	int32 longAtkRange;	// K
	int32 lonagAtkProjectileDamage;	// L
	float longAtkProjectileSpeed;	// M
	int32 longAtkProjectileCount;	// N
	std::string projetileTypeWidth;	// O
	std::string projectileTypeHeight;	// P
	int32 slashAtkDamage;	// Q

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
				case 0:this->commonStat.id = std::stoi(cell); break;	// A
				case 1: this->commonStat.hp = std::stoi(cell); break;	// B
				case 2: this->healItemDropRate = std::stof(cell); break;	// C
				case 3: this->speed = std::stof(cell); break;	// D
				case 4: this->knockBackDistance = std::stoi(cell); break;	// E
				case 5: this->backStepDistance = std::stoi(cell); break;	// F
				case 6: this->dashSpeed = std::stof(cell); break;	// G
				case 7: this->dashDistance = std::stoi(cell); break;	// H
				case 8: this->closeAtkRange = std::stoi(cell); break;	// I
				case 9: this->closeAtkDamage = std::stoi(cell); break;	// J
				case 10: this->longAtkRange = std::stoi(cell); break;	// K
				case 11: this->lonagAtkProjectileDamage = std::stoi(cell); break;	// L
				case 12: this->longAtkProjectileSpeed = std::stof(cell); break;	// M
				case 13: this->longAtkProjectileCount = std::stoi(cell); break;	// N
				case 14: this->projetileTypeWidth = cell; break;	// O
				case 15: this->projectileTypeHeight = cell; break;	// P
				case 16: this->slashAtkDamage = std::stoi(cell); break;	// Q
				}
				++column;
			}
		}
		ifs.close();
	}
};

class FinalBoss : public Monster
{
	using Super = Monster;
public:
	FinalBoss();
	virtual ~FinalBoss() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void UpdateAnimation() override;

protected:
	virtual void TickIdle() override {};
	virtual void TickMove() override {};
	virtual void TickJump() override {};
	virtual void TickCloseAttack() override {};
	virtual void TickLongAttack() override {};
	virtual void TickSkill() override {};
	virtual void TickHit() override {};
	virtual void TickDead() override {};
	virtual void TickChase() override {};
	virtual void TickRoaming() override {};
	virtual void TickReturn() override {};
	virtual void TickReturnIdle() override {};

public:
	virtual int32 GetAttack() override;
	virtual int32& GetHp() override { return _commonStat.hp; }
	virtual float GetSpeed() override { return _stat->speed; };

public:
	void CalPixelPerSecond();

private:
	FinalBossStat* _stat;
	Node* _rootNode;	// BT 최상위 노드

	Vec2 _spawnPos;
	Dir _spawnDir;
	float _moveDistance;
	Vec2 _movementLimit;

	float _currentMoveDistance;
	Collider* _attackCollider;

	int32 _currentProjectileCount = 0;
	float _sumTime = 0.f;

public:
	Player* _player;
};

