#pragma once
#include "Monster.h"

class AmateurFencer : public Monster
{
	using Super = Monster;
public:
	AmateurFencer();
	virtual ~AmateurFencer() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	bool isHpDecrease();	// Con
	bool isHpLessThanZero();	// Con
	BehaviorState Die();	// State
	BehaviorState Hurt();	// State

	bool isPcDistanceMoreThan320px();	// Con
	bool isHurtOrAtkState();	// Con
	BehaviorState Chase();	// State

	bool isChaseState();	// Con
	bool is3sPass();	// Con
	BehaviorState Idle();	// State

	bool isChaseStateorPcInside320px();	// Con

	bool isPcDistanceLessThanorEqual120px();	// Con
	BehaviorState Stab();	// Action(Âî¸£±â)
	BehaviorState BackStep();	// Action
	BehaviorState CloseAtk();	// State

	BehaviorState Dash();	// Action

	bool isCloseAtkMoreThanLongAtk();	// Con
	BehaviorState fireSword();	// Action
	BehaviorState LongAtk();	// State
};

