#pragma once
#include "Monster.h"

struct statTOW
{
	float speed;
	float chaseSpeed;

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
	virtual void TickNormalAttack() override;
	virtual void TickHit() override;
	virtual void TickDead() override;
	virtual void TickChase() override;
	virtual void TickRoaming() override;
	virtual void UpdateAnimation() override;

private:
	
};