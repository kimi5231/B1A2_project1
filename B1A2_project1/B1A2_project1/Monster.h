#pragma once
#include "Creature.h"

class Monster : public Creature
{
	using Super = Creature;
public:
	Monster();
	virtual ~Monster() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void TickIdle() override {};
	virtual void TickMove() override {};
	virtual void TickDuckDown() override {};
	virtual void TickDuckDownMove() override {};
	virtual void TickJump() override {};
	virtual void TickNormalAttack() override {};
	virtual void TickSkill() override {};
	virtual void TickHang() override {};
	virtual void TickRelease() override {};
	virtual void TickHit() override {};
	virtual void TickDead() override {};
	virtual void UpdateAnimation() override {};
};