#include "pch.h"
#include "AmateurFencer.h"
#include "BehaviorTree.h"
#include "Player.h"
#include "Slashwave.h"
#include "DevScene.h"
#include "BoxCollider.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Flipbook.h"

AmateurFencer::AmateurFencer()
{
	// Stat
	AmateurFencerStat* amateurFencerStat = new AmateurFencerStat();
	amateurFencerStat = GET_SINGLE(ResourceManager)->LoadAmateurFencerStat(L"DataBase\\amateurFencerStat.csv");
	_stat = amateurFencerStat;

	CalPixelPerSecond();

	// Flipbook
	_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookChase[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookChase[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookThrust[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookThrust[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookBackStep[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookBackStep[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookSlashWave[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookSlashWave[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookDash[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookDash[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookDead[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookDead[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");

	// Collider
	{
		// AF
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER);

			collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);

			collider->SetSize({ 31, 88 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}

		// Detection
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

AmateurFencer::~AmateurFencer()
{
}

void AmateurFencer::BeginPlay()
{
	Super::BeginPlay();

	// Idle Sequence
	Condition* c1 = new Condition("is cur state Idle?", [&]() {return is_cur_state_Idle(); });
	Action* a1 = new Action("Idle", [&]() {return Idle(); });
	Sequence* IdleSequence = new Sequence();
	IdleSequence->addChild(c1);
	IdleSequence->addChild(a1);

	// Hit Sequence
	Condition* c2 = new Condition("is cur state Hit?", [&]() {return is_cur_state_hit(); });
	Action* a2 = new Action("Hit", [&]() {return Hit(); });
	Sequence* HitSequence = new Sequence();
	HitSequence->addChild(c2);
	HitSequence->addChild(a2);

	// Chase Sequence
	Condition* c3 = new Condition("is cur state Chase?", [&]() {return is_cur_state_chase(); });
	Action* a3 = new Action("Chase", [&]() {return Chase(); });
	Sequence* ChaseSequence = new Sequence();
	ChaseSequence->addChild(c3);
	ChaseSequence->addChild(a3);

	// Attack Selector
	// Close Atk Sequence
	Condition* c4_1 = new Condition("is cur state Thrust?", [&]() {return is_cur_state_thrust(); });
	Action* a4_1 = new Action("Thrust", [&]() {return Thrust(); });
	Condition* c4_2 = new Condition("is cur state BackStep?", [&]() {return is_cur_state_backstep(); });
	Action* a4_2 = new Action("BackStep", [&]() {return BackStep(); });
	Sequence* CloseAtkSequence = new Sequence();
	CloseAtkSequence->addChild(c4_1);
	CloseAtkSequence->addChild(a4_1);
	CloseAtkSequence->addChild(c4_2);
	CloseAtkSequence->addChild(a4_2);
	
	// Long Atk Sequence
	Condition* c5_1 = new Condition("is cur state SlashWave?", [&]() {return is_cur_state_slashwave(); });
	Action* a5_1 = new Action("SlashWave", [&]() {return SlashWave(); });
	Condition* c5_2 = new Condition("is cur State Dash?", [&]() {return is_cur_state_dash(); });
	Action* a5_2 = new Action("Dash", [&]() {return Dash(); });

	Sequence* LongAtkSequence = new Sequence();
	LongAtkSequence->addChild(c5_1);
	LongAtkSequence->addChild(a5_1);
	LongAtkSequence->addChild(c5_2);
	LongAtkSequence->addChild(a5_2);

	Selector* AttackSelector = new Selector();
	AttackSelector->addChild(CloseAtkSequence);
	AttackSelector->addChild(LongAtkSequence);

	// Dead Sequence
	Condition* c6 = new Condition("is cur state Dead?", [&]() {return is_cur_state_dead(); });
	Action* a6 = new Action("Dead", [&]() {return Dead(); });
	Sequence* DeadSequence = new Sequence();
	DeadSequence->addChild(c6);
	DeadSequence->addChild(a6);

	// rootNode 설정
	Selector* RootSelector = new Selector();
	RootSelector->addChild(IdleSequence);
	RootSelector->addChild(HitSequence);
	RootSelector->addChild(ChaseSequence);
	RootSelector->addChild(AttackSelector);
	RootSelector->addChild(DeadSequence);
	_rootNode = RootSelector;

	SetState(ObjectState::Idle);
}

void AmateurFencer::Tick()
{
	Super::Tick();

	if (GetFromPlayerXDistance() >= 0)
		SetDir(DIR_LEFT);
	else
		SetDir(DIR_RIGHT);

	_pos.x = std::clamp(_pos.x, _movementLimit.x, _movementLimit.y);

	if (_rootNode)
	{
		_rootNode->run();
	}
}

void AmateurFencer::Render(HDC hdc)
{
	Super::Render(hdc);
}

void AmateurFencer::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		SetFlipbook(_flipbookIdle[_dir]);
		break;
	case ObjectState::Hit:
		SetFlipbook(_flipbookHit[_dir]);
		break;
	case ObjectState::Chase:
		SetFlipbook(_flipbookChase[_dir]);
		break;
	case ObjectState::Thrust:
		SetFlipbook(_flipbookThrust[_dir]);
		break;
	case ObjectState::BackStep:
		SetFlipbook(_flipbookBackStep[_dir]);
		break;
	case ObjectState::SlashWave:
		SetFlipbook(_flipbookSlashWave[_dir]);
		break;
	case ObjectState::Dash:
		SetFlipbook(_flipbookDash[_dir]);
		break;
	case ObjectState::Dead:
		SetFlipbook(_flipbookDead[_dir]);
		break;
	}
}

void AmateurFencer::CalPixelPerSecond()
{
	float PIXEL_PER_METER = (10.0 / 0.2);

	// Move
	{
		float MOVE_SPEED_KMPH = _stat->speed;
		float MOVE_SPEED_MPM = (MOVE_SPEED_KMPH * 1000.0 / 60.0);
		float MOVE_SPEED_MPS = (MOVE_SPEED_MPM / 60.0);
		float MOVE_SPEED_PPS = (MOVE_SPEED_MPS * PIXEL_PER_METER);

		_stat->speed = MOVE_SPEED_PPS;
	}

	// Dash
	{
		float DASH_SPEED_KMPH = _stat->dashSpeed;
		float DASH_SPEED_MPM = (DASH_SPEED_KMPH * 1000.0 / 60.0);
		float DASH_SPEED_MPS = (DASH_SPEED_MPM / 60.0);
		float DASH_SPEED_PPS = (DASH_SPEED_MPS * PIXEL_PER_METER);

		_stat->dashSpeed = DASH_SPEED_PPS;
	}

	// LongAtk Projectile 
	{
		float PROJECTILE_SPEED_KMPH = _stat->longAtkProjectileSpeed;
		float PROJECTILE_SPEED_MPM = (PROJECTILE_SPEED_KMPH * 1000.0 / 60.0);
		float PROJECTILE_SPEED_MPS = (PROJECTILE_SPEED_MPM / 60.0);
		float PROJECTILE_SPEED_PPS = (PROJECTILE_SPEED_MPS * PIXEL_PER_METER);

		_stat->longAtkProjectileSpeed = PROJECTILE_SPEED_PPS;
	}
}

int32 AmateurFencer::GetAttack()
{
	return _stat->closeAtkDamage;
}

BehaviorState AmateurFencer::is_cur_state_Idle()
{
	if (_state == ObjectState::Idle)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Idle()
{
	return BehaviorState::RUNNING;
}

BehaviorState AmateurFencer::is_cur_state_hit()
{
	if (_state == ObjectState::Hit)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Hit()
{
	if (_dir == DIR_RIGHT)
		_pos.x -= _stat->knockBackDistance;
	else
		_pos.x += _stat->knockBackDistance;

	SetState(ObjectState::Chase);

	return BehaviorState::SUCCESS;
}

BehaviorState AmateurFencer::is_cur_state_chase()
{
	if (_state == ObjectState::Chase)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Chase()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	float xDistance = GetAbsFromPlayerXDisatance();
	float yDistance = GetAbsFromPlayerYDistance();
	
	// Chase 유지
	if (GetAbsFromPlayerXDisatance() > _stat->closeAtkRange && GetAbsFromPlayerXDisatance() <= _stat->playerDetection.x)
	{
		if (GetAbsFromPlayerYDistance() > _stat->playerDetection.y)
		{
			if (_dir == DIR_RIGHT)
				_pos.x += _stat->speed * deltaTime;
			else
				_pos.x -= _stat->speed * deltaTime;
		}

		return BehaviorState::RUNNING;
	}
	
	// 근거리 or 원거리 공격
	if (GetAbsFromPlayerXDisatance() <= _stat->closeAtkRange)
	{
		SetState(ObjectState::Thrust);
		return BehaviorState::SUCCESS;
	}
	else if (std::abs(GetAbsFromPlayerXDisatance() - _stat->closeAtkRange) > std::abs(GetAbsFromPlayerXDisatance() - _stat->longAtkRange))	// |거리 - 근공사| > |거리 - 원공사| 
	{
		SetState(ObjectState::SlashWave);
		return BehaviorState::SUCCESS;
	}

	// Idle 상태 변경은 Detection Collision 충돌이 끝났을 때 호출됨
}

BehaviorState AmateurFencer::is_cur_state_thrust()
{
	if (_state == ObjectState::Thrust)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Thrust()	// 찌르기
{	
	if (!_attackCollider)
	{
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER_ATTACK);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 20, 20 });	// 스프라이트에 따라 수정 필요

			_attackCollider = collider;

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
			}
	}

	if (GetIdx() == 0)	// _flipbookThrust[_dir}->GetFlipbookEndNum()
	{
		SetState(ObjectState::BackStep);
		return BehaviorState::SUCCESS;
	}
}

BehaviorState AmateurFencer::is_cur_state_backstep()
{
	if (_state == ObjectState::BackStep)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::BackStep()
{
	if (_dir == DIR_RIGHT)
		_pos.x -= _stat->backStepDistance;
	else
		_pos.x += _stat->backStepDistance;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	float xDistance = GetAbsFromPlayerXDisatance();
	float yDistance = GetAbsFromPlayerYDistance();

	// Chase
	if (GetAbsFromPlayerXDisatance() > _stat->closeAtkRange && GetAbsFromPlayerXDisatance() <= _stat->playerDetection.x)
	{
		if (GetAbsFromPlayerYDistance() > _stat->playerDetection.y)
		{
			SetState(ObjectState::Chase);
		}

		return BehaviorState::SUCCESS;
	}

	// 근거리 or 원거리 공격
	if (GetAbsFromPlayerXDisatance() <= _stat->closeAtkRange)
	{
		SetState(ObjectState::Thrust);
		return BehaviorState::SUCCESS;
	}
	else if (std::abs(GetAbsFromPlayerXDisatance() - _stat->closeAtkRange) > std::abs(GetAbsFromPlayerXDisatance() - _stat->longAtkRange))	// |거리 - 근공사| > |거리 - 원공사| 
	{
		SetState(ObjectState::SlashWave);
		return BehaviorState::SUCCESS;
	}

}

BehaviorState AmateurFencer::is_cur_state_slashwave()
{
	if (_state == ObjectState::SlashWave)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::SlashWave()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= 0.3f)
	{
		_sumTime = 0.f;
		CreateProjectile();

		return BehaviorState::RUNNING;
	}

	if (_currentProjectileCount == _stat->longAtkProjectileCount)
	{
		_sumTime = 0.f;
		SetState(ObjectState::Dash);
		_currentProjectileCount = 0;
	
		return BehaviorState::SUCCESS;
	}
}

BehaviorState AmateurFencer::is_cur_state_dash()
{
	if (_state == ObjectState::Dash)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Dash()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime <= 0.48f)
	{
		if (_dir = DIR_RIGHT)
			_pos.x += _stat->dashSpeed * deltaTime;
		else
			_pos.x -= _stat->dashSpeed * deltaTime;
	}
	else
	{
		SetState(ObjectState::Chase);
		return BehaviorState::SUCCESS;
	}

	return BehaviorState::RUNNING;
}

BehaviorState AmateurFencer::is_cur_state_dead()
{
	if (_state == ObjectState::Dead)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Dead()
{
	// 객체 제거
	// 추후 GameScene로 변경할 예정
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	scene->RemoveActor(this);
	
	return BehaviorState::SUCCESS;
}

float AmateurFencer::GetFromPlayerXDistance()
{
	return this->GetPos().x - _player->GetPos().x;	// 양수 → 플레이어보다 오른쪽에, 음수 → 플레이어보다 왼쪽에
}

float AmateurFencer::GetAbsFromPlayerXDisatance()
{
	return std::abs(GetFromPlayerXDistance());
}

float AmateurFencer::GetFromPlayerYDistance()
{
	return this->GetPos().x - _player->GetPos().y;
}

float AmateurFencer::GetAbsFromPlayerYDistance()
{
	return std::abs(GetFromPlayerYDistance());
}

void AmateurFencer::SetSpawnPos(Vec2 pos)
{
	_spawnPos = pos;
	SetPos(_spawnPos);
}

void AmateurFencer::SetSpawnDir(Dir dir)
{
	_spawnDir = dir;
	SetDir(dir);
}

void AmateurFencer::SetMoveDistance(float distance)
{
	_moveDistance = distance;
	_currentMoveDistance = _moveDistance;
}

void AmateurFencer::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;
	
	if (b1->GetCollisionLayer() == CLT_DETECT)
	{
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			SetState(ObjectState::Chase);
			SetTarget(dynamic_cast<Player*>(b2->GetOwner()));
		}
	}

	if (b1->GetCollisionLayer() == CLT_MONSTER && b2->GetCollisionLayer() == CLT_PLAYER_ATTACK)
	{
		Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
		OnDamaged(otherOwner);
		SetTarget(dynamic_cast<Player*>(b2->GetOwner()));
	}
}

void AmateurFencer::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b1->GetCollisionLayer() == CLT_DETECT)
	{
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			SetState(ObjectState::Idle);
			SetTarget(dynamic_cast<Player*>(b2->GetOwner()));
		}
	}
}

void AmateurFencer::CreateProjectile()
{
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	Slashwave* slashwave = scene->SpawnObject<Slashwave>({ _pos.x, _pos.y }, LAYER_PLAYER);
	slashwave->SetSpeed(_stat->longAtkProjectileSpeed);
	slashwave->SetAttack(_stat->longAtkProjectileDamage);
	slashwave->SetRange(_stat->longAtkRange);
	slashwave->SetOwner(this);
	slashwave->SetDir(_dir);

	_currentProjectileCount++;
}
