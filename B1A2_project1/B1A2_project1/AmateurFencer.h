#pragma once
#include "Monster.h"

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

