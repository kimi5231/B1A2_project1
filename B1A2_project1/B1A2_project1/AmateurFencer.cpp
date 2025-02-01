#include "pch.h"
#include "AmateurFencer.h"
#include "BehaviorTree.h"

AmateurFencer::AmateurFencer()
{
}

AmateurFencer::~AmateurFencer()
{
}

void AmateurFencer::BeginPlay()
{
	// Condition Node

	// Action Node

	// Sequence Node

	// Selector Node
}

void AmateurFencer::Tick()
{
}

void AmateurFencer::Render(HDC hdc)
{
}

bool AmateurFencer::isHpDecrease()
{
	return false;
}

bool AmateurFencer::isHpLessThanZero()
{
	return false;
}

BehaviorState AmateurFencer::Die()
{
	return BehaviorState();
}

BehaviorState AmateurFencer::Hurt()
{
	return BehaviorState();
}

bool AmateurFencer::isPcDistanceMoreThan320px()
{
	return false;
}

BehaviorState AmateurFencer::Dash()
{
	return BehaviorState();
}

bool AmateurFencer::isCloseAtkMoreThanLongAtk()
{
	return false;
}

BehaviorState AmateurFencer::fireSword()
{
	return BehaviorState();
}

BehaviorState AmateurFencer::LongAtk()
{
	return BehaviorState();
}

bool AmateurFencer::isHurtOrAtkState()
{
	return false;
}

BehaviorState AmateurFencer::Chase()
{
	return BehaviorState();
}

bool AmateurFencer::isChaseState()
{
	return false;
}

bool AmateurFencer::is3sPass()
{
	return false;
}

BehaviorState AmateurFencer::Idle()
{
	return BehaviorState();
}

bool AmateurFencer::isChaseStateorPcInside320px()
{
	return false;
}

bool AmateurFencer::isPcDistanceLessThanorEqual120px()
{
	return false;
}

BehaviorState AmateurFencer::Stab()
{
	return BehaviorState();
}

BehaviorState AmateurFencer::BackStep()
{
	return BehaviorState();
}

BehaviorState AmateurFencer::CloseAtk()
{
	return BehaviorState();
}
