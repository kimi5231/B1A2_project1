#include "pch.h"
#include "TiredOfficeWorker.h"
#include "BoxCollider.h"
#include "Player.h"
#include "GameScene.h"
#include "Item.h"
#include "ItemActor.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Sound.h"

TiredOfficeWorker::TiredOfficeWorker()
{
	// Set Stat
	TiredOfficeWorkerStat* tiredOfficeWorkerStat = new TiredOfficeWorkerStat();
	tiredOfficeWorkerStat = GET_SINGLE(ResourceManager)->LoadTiredOfficeWorkerStat(L"DataBase\\tiredOfficeWorkerStat.csv");
	_stat = tiredOfficeWorkerStat;

	CalPixelPerSecond();

	// Set Flipbook
	{
		_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerIdleRight");
		_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerIdleLeft");
		_flipbookCloseAttack[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerCloseAttackRight");
		_flipbookCloseAttack[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerCloseAttackLeft");
		_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerHitRight");
		_flipbookHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerHitLeft");
		_flipbookDead[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerDeadRight");
		_flipbookDead[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerDeadLeft");
		_flipbookChase[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerChaseRight");
		_flipbookChase[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerChaseLeft");
		_flipbookRoaming[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerRoamingRight");
		_flipbookRoaming[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerRoamingLeft");
		_flipbookReturn[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerRoamingRight");
		_flipbookReturn[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerRoamingLeft");
		_flipbookReturnIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerIdleRight");
		_flipbookReturnIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerIdleLeft");
	}

	// Collider Component
	{
		// Monster Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER);

			collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);
			collider->AddCollisionFlagLayer(CLT_PLAYER_SKILL);
			collider->AddCollisionFlagLayer(CLT_GROUND);

			collider->SetSize({ 34, 80 });
			
			_collider = collider;

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

			_detectCollider = collider;

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

	TickGravity();
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
		_currentMoveDistance = _moveDistance;
		SetState(ObjectState::Roaming);
	}
}

void TiredOfficeWorker::TickCloseAttack()
{
	// Monster Attack Collider 생성
	if (!_attackCollider)
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_MONSTER_ATTACK);

		collider->AddCollisionFlagLayer(CLT_PLAYER);

		collider->SetSize({ 75, 65 });

		_attackCollider = collider;

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}
	
	// 마지막 공격 모션일 때
	if (GetIdx() == 4)
	{
		// 공격 범위 체크 (코드 정리 필요)
		if (std::abs(_target->GetPos().x - _pos.x) <= _stat->attackRange.x &&
			_target->GetPos().y >= _pos.y - (_stat->attackRange.y / 2) &&
			_target->GetPos().y <= _pos.y + (_stat->attackRange.y / 2))
			SetState(ObjectState::CloseAttack);		
		else
		{
			_sumTime = 0.f;
			SetState(ObjectState::Chase);
		}

		// Monster Attack Collider 삭제
		GET_SINGLE(CollisionManager)->RemoveCollider(_attackCollider);
		RemoveComponent(_attackCollider);
		SAFE_DELETE(_attackCollider);
	}
}

void TiredOfficeWorker::TickHit()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 스턴이 끝나면 Chase으로 변경
	if (_sumTime >= 0.5f)
	{
		_sumTime = 0.f;
		SetState(ObjectState::Chase);
	}
}

void TiredOfficeWorker::TickDead()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 스턴이 끝나면 객체 제거 후 아이템 드랍
	if (_sumTime >= 0.5f)
	{
		// 추후 GameScene로 변경할 예정
		GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

		// 난수 생성
		std::random_device rd;
		std::default_random_engine dre{ rd() };
		std::uniform_real_distribution urd{ 0.f, 1.f };

		// 아이템 드랍
		if (urd(dre) <= _stat->healtemDropRate)
		{
			// 힐템 생성
			Item* itemData = GET_SINGLE(ResourceManager)->GetItem(L"Item");
			ItemActor* Item = scene->SpawnObject<ItemActor>({ _pos.x, _pos.y }, LAYER_ITEM, 300100, itemData->GetItems());
		}

		// 객체 제거
		scene->InputDeadMonsterIdAndErasePointer(_id);
		scene->RemoveActor(this);
	}	
}

void TiredOfficeWorker::TickChase()
{
	// 범위 체크
	if (_pos.x > _movementLimit.y || _pos.x < _movementLimit.x)
	{
		_pos.x = std::clamp(_pos.x, _movementLimit.x, _movementLimit.y);
		_sumTime = 0.f;
		SetState(ObjectState::ReturnIdle);
	}

	// 추적
	if (_target->GetPos().x - _pos.x < 0)
		SetDir(DIR_LEFT);
	else
		SetDir(DIR_RIGHT);

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _stat->chaseSpeed * deltaTime;
	else
		_pos.x -= _stat->chaseSpeed * deltaTime;

	// 추적 중 놓쳤을 때
	if (_sumTime != 0.f)
	{
		_sumTime += deltaTime;

		// 3초가 지니면 복귀
		if (_sumTime >= 3.0f)
			SetState(ObjectState::Return);
	}

	// 공격 범위 체크 (코드 정리 필요)
	if (std::abs(_target->GetPos().x - _pos.x) <= _stat->attackRange.x && 
		_target->GetPos().y >= _pos.y - (_stat->attackRange.y / 2) &&
		_target->GetPos().y <= _pos.y + (_stat->attackRange.y / 2))
		SetState(ObjectState::CloseAttack);
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
		_sumTime = 0.f;
		SetState(ObjectState::Idle);

		// 방향 전환
		if (_dir == DIR_RIGHT)
			SetDir(DIR_LEFT);
		else
			SetDir(DIR_RIGHT);
	}
}

void TiredOfficeWorker::TickReturn()
{
	if (_pos.x > _spawnPos.x)
		SetDir(DIR_LEFT);
	else
		SetDir(DIR_RIGHT);

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _stat->speed * deltaTime;
	else
		_pos.x -= _stat->speed * deltaTime;

	// 위치 확인
	if (_dir == DIR_LEFT)
		_pos.x = max(_spawnPos.x, _pos.x);
	else
		_pos.x = min(_pos.x, _spawnPos.x);

	if (_pos.x == _spawnPos.x)
	{
		_sumTime = 0.f;
		SetState(ObjectState::Idle);
		SetPos(_spawnPos);
		SetDir(_spawnDir);
	}
}

void TiredOfficeWorker::TickReturnIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= _stat->idleTime)
		SetState(ObjectState::Return);
}

void TiredOfficeWorker::UpdateAnimation()
{
	Vec2 colliderSize = _collider->GetSize();

	switch (_state)
	{
	case ObjectState::Idle:
		SetFlipbook(_flipbookIdle[_dir]);
		_collider->SetSize({34, 80});
		break;
	case ObjectState::CloseAttack:
		SetFlipbook(_flipbookCloseAttack[_dir]);
		_collider->SetSize({ 95, 105 });
		{
			Sound* sound = GET_SINGLE(ResourceManager)->GetSound(L"TowCloseAtk");
			sound->Play(false);
		}
		break;
	case ObjectState::Hit:
		SetFlipbook(_flipbookHit[_dir]);
		_collider->SetSize({ 50, 70 });
		break;
	case ObjectState::Dead:
		SetFlipbook(_flipbookDead[_dir]);
		_collider->SetSize({ 60, 78 });
		break;
	case ObjectState::Chase:
		SetFlipbook(_flipbookChase[_dir]);
		_collider->SetSize({ 97, 77 });
		break;
	case ObjectState::Roaming:
		SetFlipbook(_flipbookRoaming[_dir]);
		_collider->SetSize({ 50, 81 });
		break;
	case ObjectState::Return:
		SetFlipbook(_flipbookReturn[_dir]);
		_collider->SetSize({ 50, 81 });
		break;
	case ObjectState::ReturnIdle:
		SetFlipbook(_flipbookReturnIdle[_dir]);
		_collider->SetSize({ 34, 80 });
		break;
	}

	if (colliderSize.y > _collider->GetSize().y)
	{
		_isGround = false;
		_isAir = true;
	}
}

void TiredOfficeWorker::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	// 피격 > 추적

	// 부딪힌 자신의 collider가 CLT_MONSTER일 때
	if (b1->GetCollisionLayer() == CLT_MONSTER)
	{
		// Player Attack과 충돌
 		if (b2->GetCollisionLayer() == CLT_PLAYER_ATTACK)
		{
			_sumTime = 0.f;
			Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
			OnDamaged(otherOwner);
			SetTarget(dynamic_cast<Player*>(b2->GetOwner()));
			
			// knockback
			if (_dir == DIR_RIGHT)
				_pos.x -= _stat->knockBackDistance;
			else
				_pos.x += _stat->knockBackDistance;
		}
		else if (b2->GetCollisionLayer() == CLT_PLAYER_SKILL)
		{
			_sumTime = 0.f;
			Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
			OnDamagedNoHit(otherOwner);
			SetTarget(dynamic_cast<Player*>(b2->GetOwner()));
		}
		
		if (b2->GetCollisionLayer() == CLT_GROUND)
		{
			_isGround = true;
			_isAir = false;

			AdjustCollisionPosGround(b1, b2);
		}

		return;
	}

	// 부딪힌 자신의 collider가 CLT_DETECT일 때
	if (b1->GetCollisionLayer() == CLT_DETECT)
	{
		// Player와 충돌
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			_sumTime = 0.f;
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
			// 놓친 시간 측정 시작
 			float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
			_sumTime += deltaTime;
		}
	}
}

void TiredOfficeWorker::AdjustCollisionPosGround(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	Vec2 pos = GetPos();
	Vec2 colliderPos = _collider->GetPos();

	// 충돌 범위
	RECT intersect = {};

	if (::IntersectRect(&intersect, &r1, &r2))
	{
		int32 h = intersect.bottom - intersect.top;

		// 위로 올려 보내기
		pos.y -= h;
		colliderPos.y -= h;
	}

	SetPos(pos);
	_collider->SetPos(colliderPos);
}

void TiredOfficeWorker::SetSpawnPos(Vec2 pos)
{
	_spawnPos = pos;
	SetPos(_spawnPos);
}

void TiredOfficeWorker::SetSpawnDir(Dir dir)
{
	_spawnDir = dir;
	SetDir(dir);
}

void TiredOfficeWorker::SetMoveDistance(float distance)
{
	_moveDistance = distance;
	_currentMoveDistance = _moveDistance;
}

float TiredOfficeWorker::GetSpeed()
{
	switch (_state)
	{
	case ObjectState::Move:
		return _stat->speed;
		break;
	case ObjectState::Chase:
		return _stat->chaseSpeed;
		break;
	}
}

int32 TiredOfficeWorker::GetAttack()
{
	switch (_state)
	{
	case ObjectState::CloseAttack:
		return _stat->attack;
		break;
	}
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