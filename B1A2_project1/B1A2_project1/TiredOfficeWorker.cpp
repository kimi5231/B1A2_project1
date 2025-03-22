#include "pch.h"
#include "TiredOfficeWorker.h"
#include "BoxCollider.h"
#include "Player.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"

TiredOfficeWorker::TiredOfficeWorker()
{
	TiredOfficeWorkerStat* tiredOfficeWorkerStat = new TiredOfficeWorkerStat();
	tiredOfficeWorkerStat = GET_SINGLE(ResourceManager)->LoadTiredOfficeWorkerStat(L"DataBase\\tiredOfficeWorkerStat.csv");
	_stat = tiredOfficeWorkerStat;

	CalPixelPerSecond();

	_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
	_flipbookChase[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
	_flipbookChase[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
	_flipbookRoaming[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
	_flipbookRoaming[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");

	// Collider Component
	{
		// Monster Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER);

			collider->SetSize({ 31, 77 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
		
		// Monster Detection Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_DETECT);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ float(_stat->playerDetection.x), float(_stat->playerDetection.y) });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
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
		SetState(ObjectState::Roaming);
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
	if (_target->GetPos().x - _pos.x < 0)
		SetDir(DIR_LEFT);
	else
		SetDir(DIR_RIGHT);

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _stat->chaseSpeed * deltaTime;
	else
		_pos.x -= _stat->chaseSpeed * deltaTime;

	// 놓치기

}

void TiredOfficeWorker::TickRoaming()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if(_dir == DIR_RIGHT)
		_pos.x += _stat->speed * deltaTime;
	else
		_pos.x -= _stat->speed * deltaTime;

	_currentMoveDistance -= _stat->speed * deltaTime;

	if (_currentMoveDistance <= 0.f)
	{
		_currentMoveDistance = _moveDistance;
		SetState(ObjectState::Idle);

		if (_dir == DIR_RIGHT)
			SetDir(DIR_LEFT);
		else
			SetDir(DIR_RIGHT);
	}
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
	case ObjectState::Roaming:
		SetFlipbook(_flipbookRoaming[_dir]);
		break;
	}
}

void TiredOfficeWorker::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	// 부딪힌 자신의 collider가 CLT_DETECT일 때
	if (b1->GetCollisionLayer() == CLT_DETECT)
	{
		// Player와 충돌
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			SetState(ObjectState::Chase);
			SetTarget(dynamic_cast<Player*>(b2->GetOwner()));
		}
	}
}

void TiredOfficeWorker::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	// 부딪힌 자신의 collider가 CLT_DETECT일 때
	if (b1->GetCollisionLayer() == CLT_DETECT)
	{
		// Player와 충돌
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			// 시간 재는 코드 추가 예정
		}
	}
}

void TiredOfficeWorker::SetSpawnPos(Vec2 pos)
{
	_spawnPos = pos;
	_pos = _spawnPos;
}

void TiredOfficeWorker::SetMoveDistance(float distance)
{
	_moveDistance = distance;
	_currentMoveDistance = _moveDistance;
}

void TiredOfficeWorker::CalPixelPerSecond()
{
	float PIXEL_PER_METER = (10.0 / 0.2);

	// Move(Roaming)
	{
		float MOVE_SPEED_KMPH = _stat->speed;
		float MOVE_SPEED_MPM = (MOVE_SPEED_KMPH * 1000.0 / 60.0);
		float MOVE_SPEED_MPS = (MOVE_SPEED_MPM / 60.0);
		float MOVE_SPEED_PPS = (MOVE_SPEED_MPS * PIXEL_PER_METER);

		_stat->speed = MOVE_SPEED_PPS;
	}

	// Chase
	{
		float CHASE_SPEED_KMPH = _stat->chaseSpeed;
		float CHASE_SPEED_MPM = (CHASE_SPEED_KMPH * 1000.0 / 60.0);
		float CHASE_SPEED_MPS = (CHASE_SPEED_MPM / 60.0);
		float CHASE_SPEED_PPS = (CHASE_SPEED_MPS * PIXEL_PER_METER);

		_stat->chaseSpeed = CHASE_SPEED_PPS;
	}
}