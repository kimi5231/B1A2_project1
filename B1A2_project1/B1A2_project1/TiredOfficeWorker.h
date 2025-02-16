#pragma once
#include "Monster.h"

struct TiredOfficeWorkerStat
{
	CommonStat commonStat;
	float healtemDropRate;
	float speed;
	float chaseSpeed;
	int32 playerDetectionX;
	int32 playerDetectionY;
	int32 knockBackDistance;
	int32 attackRange;
	int32 attack;
	float idleTime;
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
	// Flipbook
	Flipbook* _flipbookIdle[2] = {};
	Flipbook* _flipbookNormalAttack[2] = {};
	Flipbook* _flipbookHit[2] = {};
	Flipbook* _flipbookDead[2] = {};
	Flipbook* _flipbookChase[2] = {};
	Flipbook* _flipbookRoaming[2] = {};

private:
	TiredOfficeWorkerStat _stat;
	float _sumTime = 0.f;
};