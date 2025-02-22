#pragma once
#include "Monster.h"

enum class BehaviorState;

struct AmateurFencerStat
{
	CommonStat commonStat;	// A, B
	float healtemDropRate;	// C
	float speed;	// D
	int32 playerDetectionX;	// E
	int32 playerDetectionY;	// F
	int32 knockBackDistance; // G
	int32 backStaepDistance;	// H
	int32 closeAtkRange;	// I
	int32 closeAtkDamage;	// J
	int32 dashSpeed;	// K
	int32 dashDistance;	// L
	int32 longAtkRange;	// M
	int32 longAtkProjectileSpeed;	// N
	int32 longAtkProjectileDamage;	// O
	int32 longAtkProjectileCount;	// P

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
				case 2: this->healtemDropRate = std::stof(cell); break;	// C
				case 3: this->speed = std::stof(cell); break;	// D
				case 4: this->playerDetectionX = std::stoi(cell); break;	// E
				case 5: this->playerDetectionY = std::stoi(cell); break;	// F
				case 6: this->knockBackDistance = std::stoi(cell); break;	// G
				case 7: this->backStaepDistance = std::stoi(cell); break;	// H
				case 8: this->closeAtkRange = std::stoi(cell); break;	// I
				case 9: this->closeAtkDamage = std::stoi(cell); break;	// J
				case 10: this->dashSpeed = std::stoi(cell); break;	// K
				case 11: this->dashDistance = std::stoi(cell); break;	// L
				case 12: this->longAtkRange = std::stoi(cell); break;	// M
				case 13: this->longAtkProjectileSpeed = std::stoi(cell); break;	// N
				case 14: this->longAtkProjectileDamage = std::stoi(cell); break;	// O
				case 15: this->longAtkProjectileCount = std::stoi(cell); break;	// P
				}
				++column;
			}
		}
		ifs.close();
	}
};

class AmateurFencer : public Monster
{
	using Super = Monster;
public:
	AmateurFencer();
	virtual ~AmateurFencer() override;

	virtual void BeginPlay() override;		// Build BT
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	// Player에게 공격 -> HP 감소 함수(관찰자 패턴으로 구현)
	// ...

	// Idle Sequence
	BehaviorState is_cur_state_Idle();
	BehaviorState Idle();

	// Attacked Sequence
	BehaviorState is_cur_state_hit();
	BehaviorState Hit();

	// Chase Sequence
	BehaviorState is_cur_state_chase();
	BehaviorState Chase();

	// Close Attack Sequence
	BehaviorState is_cur_state_close_atk();
	BehaviorState Close_atk();

	// Long Attack Sequence
	BehaviorState is_cur_state_long_atk();
	BehaviorState Long_atk();
	BehaviorState is_cur_state_dash();
	BehaviorState Dash();

	// 참고) 멤버 변수
	//Vec2 _speed = {};
	//Dir _dir = DIR_LEFT;
	//ObjectState _state = ObjectState::Idle;
};

