#include "pch.h"
#include "BrokenCopyMachine.h"
#include "Paper.h"
#include "DevScene.h"
#include "BoxCollider.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

BrokenCopyMachine::BrokenCopyMachine()
{
	BrokenCopyMachineStat* brokenCopyMachineStat = new BrokenCopyMachineStat();
	brokenCopyMachineStat = GET_SINGLE(ResourceManager)->LoadBrokenCopyMachineStat(L"DataBase\\brokenCopyMachineStat.csv");
	_stat = brokenCopyMachineStat;

	CalPixelPerSecond();

	// SetFlipbook
	{
		_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookLongAttack[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookLongAttack[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookDead[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookDead[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
	}

	// Collider Component
	{
		// Monster Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER);

			collider->SetSize({ 55, 55 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

BrokenCopyMachine::~BrokenCopyMachine()
{
}

void BrokenCopyMachine::BeginPlay()
{
	Super::BeginPlay();
}

void BrokenCopyMachine::Tick()
{
	Super::Tick();
}

void BrokenCopyMachine::Render(HDC hdc)
{
	Super::Render(hdc);
}

void BrokenCopyMachine::TickIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= _stat->attackCoolTime)
	{
		_sumTime = 0.f;
		SetState(ObjectState::LongAttack);
	}
}

void BrokenCopyMachine::TickLongAttack()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 투사체 생성
	if (_sumTime >= 0.3f)
	{
		_sumTime = 0.f;
		CreateProjectile();
	}

	if (_currentProjectileCount == _stat->projectileCount)
	{
		_sumTime = 0.f;
		SetState(ObjectState::Idle);
		_currentProjectileCount = 0;
	}
}

void BrokenCopyMachine::TickHit()
{
	_sumTime = 0.f;
	SetState(ObjectState::Idle);
}

void BrokenCopyMachine::TickDead()
{
	// 아이템 드랍
}

void BrokenCopyMachine::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		SetFlipbook(_flipbookIdle[_dir]);
		break;
	case ObjectState::LongAttack:
		SetFlipbook(_flipbookLongAttack[_dir]);
		break;
	case ObjectState::Hit:
		SetFlipbook(_flipbookHit[_dir]);
		break;
	case ObjectState::Dead:
		SetFlipbook(_flipbookDead[_dir]);
		break;
	}
}

void BrokenCopyMachine::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	// Player Attack과 충돌
	// 추후 CLT_PLAYER_ATTACK로 변경할 예정
	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
		OnDamaged(otherOwner);
	}
}

void BrokenCopyMachine::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

int32 BrokenCopyMachine::GetAttack()
{
	switch (_state)
	{
	case ObjectState::LongAttack:
		return _stat->projectileAttack;
		break;
	}
}

void BrokenCopyMachine::CalPixelPerSecond()
{
	float PIXEL_PER_METER = (10.0 / 0.2);

	// Move
	{
		float MOVE_SPEED_KMPH = _stat->projectileSpeed;
		float MOVE_SPEED_MPM = (MOVE_SPEED_KMPH * 1000.0 / 60.0);
		float MOVE_SPEED_MPS = (MOVE_SPEED_MPM / 60.0);
		float MOVE_SPEED_PPS = (MOVE_SPEED_MPS * PIXEL_PER_METER);

		_stat->projectileSpeed = MOVE_SPEED_PPS;
	}
}

void BrokenCopyMachine::CreateProjectile()
{
	// 추후 GameScene으로 변경
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	// 추후 Layer, Pos 변경 예정
	Paper* paper = scene->SpawnObject<Paper>({ _pos.x, _pos.y}, LAYER_PLAYER);
	paper->SetSpeed(_stat->projectileSpeed);
	paper->SetAttack(_stat->projectileAttack);
	paper->SetRange(_stat->attackRange);
	paper->SetOwner(this);

	_currentProjectileCount++;
}