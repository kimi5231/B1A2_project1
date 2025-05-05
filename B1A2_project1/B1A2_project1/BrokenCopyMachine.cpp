#include "pch.h"
#include "BrokenCopyMachine.h"
#include "Paper.h"
#include "DevScene.h"
#include "BoxCollider.h"
#include "ItemActor.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

BrokenCopyMachine::BrokenCopyMachine()
{
	// Set Stat
	BrokenCopyMachineStat* brokenCopyMachineStat = new BrokenCopyMachineStat();
	brokenCopyMachineStat = GET_SINGLE(ResourceManager)->LoadBrokenCopyMachineStat(L"DataBase\\brokenCopyMachineStat.csv");
	_stat = brokenCopyMachineStat;

	CalPixelPerSecond();

	// Set Flipbook
	{
		_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineIdleRight");
		_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineIdleLeft");
		_flipbookLongAttack[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineLongAttackRight");
		_flipbookLongAttack[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineLongAttackLeft");
		_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineHitRight");
		_flipbookHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineHitLeft");
		_flipbookDead[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineDeadRight");
		_flipbookDead[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineDeadLeft");
	}

	// Collider Component
	{
		// Monster Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER);

			collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);

			collider->SetSize({ 40, 55 });

			_collider = collider;

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

BrokenCopyMachine::~BrokenCopyMachine()
{
	GET_SINGLE(CollisionManager)->RemoveCollider(_collider);
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
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 스턴이 끝나면 Idle로 변경
	if (_sumTime >= 0.5f)
	{
		_sumTime = 0.f;
		SetState(ObjectState::Idle);
	}
}

void BrokenCopyMachine::TickDead()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 스턴이 끝나면 객체 제거 후 아이템 드랍
	if (_sumTime >= 0.5f)
	{
		// 난수 생성
		std::random_device rd;
		std::default_random_engine dre{ rd() };
		std::uniform_real_distribution urd{ 0.f, 1.f };

		// 추후 GameScene로 변경할 예정
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		
		// 아이템 드랍
		if (urd(dre) <= _stat->healtemDropRate)
		{
			//ItemActor* Item = scene->SpawnObject<ItemActor>({ _pos.x, _pos.y }, LAYER_ITEM, );
		}
		
		scene->RemoveActor(this);
	}
}

void BrokenCopyMachine::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		SetFlipbook(_flipbookIdle[_dir]);
		_collider->SetSize({ 40, 55 });
		break;
	case ObjectState::LongAttack:
		SetFlipbook(_flipbookLongAttack[_dir]);
		_collider->SetSize({ 44, 61 });
		break;
	case ObjectState::Hit:
		SetFlipbook(_flipbookHit[_dir]);
		_collider->SetSize({ 43, 59 });
		break;
	case ObjectState::Dead:
		SetFlipbook(_flipbookDead[_dir]);
		_collider->SetSize({ 45, 75 });
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
	if (b2->GetCollisionLayer() == CLT_PLAYER_ATTACK)
	{
		_sumTime = 0.f;
		Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
		OnDamaged(otherOwner);
	}
}

void BrokenCopyMachine::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

float BrokenCopyMachine::GetSpeed()
{
	return 0.0f;
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

	Paper* paper = scene->SpawnObject<Paper>({ _pos.x, _pos.y}, LAYER_PROJECTILE);
	paper->SetSpeed(_stat->projectileSpeed);
	paper->SetAttack(_stat->projectileAttack);
	paper->SetRange(_stat->attackRange);
	paper->SetOwner(this);

	_currentProjectileCount++;
}