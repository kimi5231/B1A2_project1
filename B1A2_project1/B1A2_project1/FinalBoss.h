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
	int32 longAtkProjectileDamage;	// L
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
				case 11: this->longAtkProjectileDamage = std::stoi(cell); break;	// L
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


protected:
	virtual void TickIdle() override {};
	virtual void TickMove() override {};
	virtual void TickJump() override {};
	virtual void TickCloseAttack() override {};
	virtual void TickLongAttack() override {};
	virtual void TickHit() override {};
	virtual void TickDead() override {};
	virtual void TickChase() override {};
	virtual void TickRoaming() override {};
	virtual void TickReturn() override {};
	virtual void TickReturnIdle() override {};

	virtual void UpdateAnimation() override;

public:
	virtual int32 GetAttack() override;
	virtual int32& GetHp() override { return _commonStat.hp; }
	virtual float GetSpeed() override { return _stat->speed; };
	virtual Vec2Int GetPlayerDetection() { return { 0, 0 }; }

public:
	void CalPixelPerSecond();

	// Idle Sequence
	BehaviorState is_cur_state_idle();
	BehaviorState Idle();

	// Hit Sequeucne
	BehaviorState is_cur_state_hit();
	BehaviorState Hit();

	// Dead Sequence;
	BehaviorState is_cur_state_dead();
	BehaviorState Dead();

	// 수정 소환 Sequence
	BehaviorState is_cur_state_projectile_fall();
	BehaviorState ProjectileFall();
	BehaviorState is_cur_state_crystal_creation();
	BehaviorState CrystalCreation();

	// 몬스터 소환 Sequence
	BehaviorState is_cur_state_monster_creation();
	BehaviorState MonsterCreation();

	// CloseAtk Sequence
	BehaviorState is_cur_state_thrust();
	BehaviorState Thrust();
	BehaviorState is_cur_state_backstep();
	BehaviorState BackStep();

	// LongAtk Sequence
	BehaviorState is_cur_state_slashwave();
	BehaviorState SlashWave();
	BehaviorState is_cur_state_dash();
	BehaviorState Dash();

	// 순간 이동 Sequence
	BehaviorState is_cur_state_teleport();
	BehaviorState Teleport();

	// 마구 베기 Sequence
	BehaviorState is_cur_state_cut_severely();
	BehaviorState CutSeverely();

public:
	float GetFromPlayerXDistance();
	float GetAbsFromPlayerXDisatance();

	void SetSpawnPos(Vec2 pos);
	void SetSpawnDir(Dir dir);
	void SetMoveDistance(float distance);
	void SetMovementLimit(Vec2 limit) { _movementLimit = limit; }

	void SetPlayer(Player* player) { _player = player; }

public:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void CreateProjectile();	// Long Atk
	void CreateProjectileFall();	// Projectile Fall
	void CreateBlanket();
	void CreateMonster();

	void SubtractCurrentCrystalCount(int32) { _currentCrystalCount--; }

private:
	// Flipbook
	Flipbook* _flipbookIdle[2] = {};
	Flipbook* _flipbookHit[2] = {};
	Flipbook* _flipbookDead[2] = {};
	// 수정 소환 & 몬스터 소환 Flipbook은 Idle로 임시 설정
	Flipbook* _flipbookThrust[2] = {};
	Flipbook* _flipbookBackStep[2] = {};
	Flipbook* _flipbookSlashWave[2] = {};
	Flipbook* _flipbookDash[2] = {};
	Flipbook* _flipbookTeleport[2] = {};
	Flipbook* _flipbookCutSeverely[2] = {};

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
	int32 _currentMonsterCreationCount = 0;		// 생성할 때
	int32 _currentMonsterCount = 0;		// 생성 후
	int32 _currentCrystalCount = 0;
	float _sumTime = 0.f;

	bool _isPlayerInSameFloor = false;		// 추적해야 함!

	bool _isFirstCrystalCreationWork = false;
	bool _isSecondCrystalCreationWork = false;
	bool _isThirdCrystalCreationWork = false;

	bool _isCrystalSpawned = false;
public:
	Player* _player;
};

