#pragma once
#include "Monster.h"

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
	virtual void TickCloseAttack() override;
	virtual void TickLongAttack() override;
	virtual void TickHit() override;
	virtual void TickDead() override;
	virtual void UpdateAnimation() override;

public:
	virtual Vec2Int GetPlayerDetection() { return {0, 0}; };

private:
	// Flipbook
	Flipbook* _flipbookIdle[2] = {};
	Flipbook* _flipbookNormalAttack[2] = {};
	Flipbook* _flipbookHit[2] = {};
	Flipbook* _flipbookDead[2] = {};
};