#include "pch.h"
#include "TiredOfficeWorker.h"
#include "BoxCollider.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"

TiredOfficeWorker::TiredOfficeWorker()
{
	TiredOfficeWorkerStat* tiredOfficeWorkerStat = new TiredOfficeWorkerStat();
	tiredOfficeWorkerStat = GET_SINGLE(ResourceManager)->LoadTiredOfficeWorkerStat(L"DataBase\\tiredOfficeWorkerStat.csv");
	_stat = tiredOfficeWorkerStat;

	_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
	_flipbookChase[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
	_flipbookChase[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");

	// Collider Component
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_MONSTER);

		collider->AddCollisionFlagLayer(CLT_PLAYER);
		collider->AddCollisionFlagLayer(CLT_GROUND);
		collider->AddCollisionFlagLayer(CLT_WALL);

		collider->SetSize({ 31, 77 });

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}
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

	if (_sumTime >= _stat->idleTime)
	{
		_sumTime = 0.f;
		SetState(ObjectState::Chase);
	}
	else
	{
		
	}
}

void TiredOfficeWorker::TickCloseAttack()
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
	_pos.x += _stat->speed;
}

void TiredOfficeWorker::TickRoaming()
{
}

void TiredOfficeWorker::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		SetFlipbook(_flipbookIdle[_dir]);
		break;
	case ObjectState::Chase:
		SetFlipbook(_flipbookChase[_dir]);
		break;
	}
}
