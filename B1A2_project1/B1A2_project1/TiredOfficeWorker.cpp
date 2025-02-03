#include "pch.h"
#include "TiredOfficeWorker.h"
#include "TimeManager.h"

TiredOfficeWorker::TiredOfficeWorker()
{
}

TiredOfficeWorker::~TiredOfficeWorker()
{
}

void TiredOfficeWorker::BeginPlay()
{
	Super::BeginPlay();
}

void TiredOfficeWorker::Tick()
{
	Super::Tick();
}

void TiredOfficeWorker::Render(HDC hdc)
{
	Super::Render(hdc);
}

void TiredOfficeWorker::TickIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= _stat.idleTime)
	{
		_sumTime = 0.f;
		SetState(ObjectState::Chase);
	}
	else
	{
		
	}
}

void TiredOfficeWorker::TickNormalAttack()
{
}

void TiredOfficeWorker::TickHit()
{
}

void TiredOfficeWorker::TickDead()
{
}

void TiredOfficeWorker::TickChase()
{
}

void TiredOfficeWorker::TickRoaming()
{
}

void TiredOfficeWorker::UpdateAnimation()
{
}
