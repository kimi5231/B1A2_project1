#include "pch.h"
#include "FinalBoss.h"
#include "ResourceManager.h"
#include "BehaviorTree.h"
#include "Player.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "Flipbook.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "SlashWave2.h"

FinalBoss::FinalBoss()
{
	// Stat
	FinalBossStat* finalBossStat = new FinalBossStat();
	finalBossStat = GET_SINGLE(ResourceManager)->LoadFinalBossStat(L"DataBase\\finalBossStat.csv");
	_stat = finalBossStat;

	CalPixelPerSecond();

	// Flipbook
	_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookDead[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookDead[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookThrust[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookThrust[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookBackStep[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookBackStep[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookSlashWave[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookSlashWave[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookDash[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookDash[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookTeleport[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookTeleport[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookCutSeverely[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");
	_flipbookCutSeverely[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBoss");

	// Collider
	{
		// Final Boss
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER);

			collider->SetCollisionLayer(CLT_PLAYER_ATTACK);

			collider->SetSize({ 30, 80 });	// 수정 필요

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}

	}
}

FinalBoss::~FinalBoss()
{
}

void FinalBoss::BeginPlay()
{
	Super::BeginPlay();

	// Idle Sequence
	Condition* c1 = new Condition("is cur state Idle?", [&]() {return is_cur_state_idle(); });
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

	// Dead Sequence
	Condition* c3 = new Condition("is cur state Dead?", [&]() {return is_cur_state_dead(); });
	Action* a3 = new Action("Dead", [&]() {return Dead(); });
	Sequence* DeadSequence = new Sequence();
	DeadSequence->addChild(c3);
	DeadSequence->addChild(a3);

	// 수정 소환 Sequence
	Condition* c4 = new Condition("is cur state Projectile Fall?", [&]() {return is_cur_state_projectile_fall(); });
	Action* a4 = new Action("ProjectileFall", [&]() {return ProjectileFall(); });;
	Condition* c5 = new Condition("is cur state Crystal Creation?", [&]() {return is_cur_state_crystal_creation(); });
	Action* a5 = new Action("CrystalCreation", [&]() {return CrystalCreation(); });
	Sequence* CrystalCreationSequence = new Sequence();
	CrystalCreationSequence->addChild(c4);
	CrystalCreationSequence->addChild(a4);
	CrystalCreationSequence->addChild(c5);
	CrystalCreationSequence->addChild(a5);

	// Monster Creation Sequeuce
	Condition* c6 = new Condition("is cur state Monster Creation?", [&]() {return is_cur_state_monster_creation(); });
	Action* a6 = new Action("MonsterCreation", [&]() {return MonsterCreation(); });
	Sequence* MonsterCreationSequence = new Sequence();
	MonsterCreationSequence->addChild(c6);
	MonsterCreationSequence->addChild(a6);

	// Attack Selector
	// Close Atk Sequence
	Condition* c7_1 = new Condition("is cur state Thrust?", [&]() {return is_cur_state_thrust(); });
	Action* a7_1 = new Action("Thrust", [&]() {return Thrust(); });
	Condition* c7_2 = new Condition("is cur state BackStep?", [&]() {return is_cur_state_backstep(); });
	Action* a7_2 = new Action("BackStep", [&]() {return BackStep(); });
	Sequence* CloseAtkSequence = new Sequence();
	CloseAtkSequence->addChild(c7_1);
	CloseAtkSequence->addChild(a7_1);
	CloseAtkSequence->addChild(c7_2);
	CloseAtkSequence->addChild(a7_2);

	// Long Atk Sequence
	Condition* c8_1 = new Condition("is cur state SlashWave?", [&]() {return is_cur_state_slashwave(); });
	Action* a8_1 = new Action("SlashWave", [&]() {return SlashWave(); });
	Condition* c8_2 = new Condition("is cur State Dash?", [&]() {return is_cur_state_dash(); });
	Action* a8_2 = new Action("Dash", [&]() {return Dash(); });
	Sequence* LongAtkSequence = new Sequence();
	LongAtkSequence->addChild(c8_1);
	LongAtkSequence->addChild(a8_1);
	LongAtkSequence->addChild(c8_2);
	LongAtkSequence->addChild(a8_2);

	Selector* AttackSelector = new Selector();
	AttackSelector->addChild(CloseAtkSequence);
	AttackSelector->addChild(LongAtkSequence);

	// Teleport Sequence
	Condition* c9 = new Condition("is cur state teleport?", [&]() {return is_cur_state_teleport(); });
	Action* a9 = new Action("Teleport", [&]() {return Teleport(); });
	// Atk Selector 
	// Cut Severely Sequence
	Condition* c10 = new Condition("is cur state cut severely?", [&]() {return is_cur_state_cut_severely(); });
	Action* a10 = new Action("CutSeverely", [&]() {return CutSeverely(); });
	Sequence* CutSeverelySequence = new Sequence();
	CutSeverelySequence->addChild(c10);
	CutSeverelySequence->addChild(a10);
	
	Selector* TeleportAtkSelector = new Selector();
	TeleportAtkSelector->addChild(CloseAtkSequence);
	TeleportAtkSelector->addChild(CutSeverelySequence);

	Sequence* TeleportSequence = new Sequence();
	TeleportSequence->addChild(c9);
	TeleportSequence->addChild(a9);
	TeleportSequence->addChild(TeleportAtkSelector);

	// rootNode 설정
	Selector* RootSelector = new Selector();
	RootSelector->addChild(IdleSequence);
	RootSelector->addChild(HitSequence);
	RootSelector->addChild(DeadSequence);
	RootSelector->addChild(CrystalCreationSequence);
	RootSelector->addChild(MonsterCreationSequence);
	RootSelector->addChild(AttackSelector);
	RootSelector->addChild(TeleportSequence);
	_rootNode = RootSelector;
}

void FinalBoss::Tick()
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

void FinalBoss::Render(HDC hdc)
{
	Super::Render(hdc);
}

void FinalBoss::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		SetFlipbook(_flipbookIdle[_dir]);
		break;
	case ObjectState::Hit:
		SetFlipbook(_flipbookHit[_dir]);
		break;
	case ObjectState::Dead:
		SetFlipbook(_flipbookDead[_dir]);
		break;
	case ObjectState::ProjectileFall:
		SetFlipbook(_flipbookIdle[_dir]);
		break;
	case ObjectState::CrystalCreation:
		SetFlipbook(_flipbookIdle[_dir]);
		break;
	case ObjectState::MonsterCreation:
		SetFlipbook(_flipbookIdle[_dir]);
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
	case ObjectState::Teleport:
		SetFlipbook(_flipbookIdle[_dir]);
		break;
	case ObjectState::CutSeverely:
		SetFlipbook(_flipbookCutSeverely[_dir]);
		break;
	}
}

int32 FinalBoss::GetAttack()
{
	switch (_state)
	{
	case ObjectState::CloseAttack:
		return _stat->closeAtkDamage;
		break;
	}
}

void FinalBoss::CalPixelPerSecond()
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

BehaviorState FinalBoss::is_cur_state_idle()
{
	if (_state == ObjectState::Idle)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Idle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	float XDistance = GetAbsFromPlayerXDisatance();

	// Idle 유지

	// 대쉬 or 순간이동
	if (XDistance >= _stat->longAtkRange)
	{
		// 같은 층에 있을 때
		{
			SetState(ObjectState::Dash);
			return BehaviorState::SUCCESS;
		}

		// 다른 층에 있을 때

	}
	
	// 근거리 or 원거리 공격
	if (XDistance <= _stat->closeAtkRange)
	{
		SetState(ObjectState::CloseAttack);
		return BehaviorState::SUCCESS;
	}
	else if (std::abs(XDistance - _stat->closeAtkRange) > std::abs(_stat->longAtkRange - XDistance))
	{
		SetState(ObjectState::LongAttack);
		return BehaviorState::SUCCESS;
	}


	// 상태 지정
	// ...

	return BehaviorState::RUNNING;
}

BehaviorState FinalBoss::is_cur_state_hit()
{
	if (_state == ObjectState::Hit)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Hit()
{
	if (_dir == DIR_RIGHT)
		_pos.x -= _stat->knockBackDistance;
	else
		_pos.x += _stat->knockBackDistance;

	SetState(ObjectState::Idle);

	return BehaviorState::SUCCESS;
}

BehaviorState FinalBoss::is_cur_state_dead()
{
	if (_state == ObjectState::Dead)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Dead()
{
	// 객체 제거
	// 추후 GameScene로 변경할 예정
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	scene->RemoveActor(this);

	return BehaviorState::SUCCESS;
}

BehaviorState FinalBoss::is_cur_state_projectile_fall()
{
	if (_state == ObjectState::ProjectileFall)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::ProjectileFall()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_crystal_creation()
{
	if (_state == ObjectState::CrystalCreation)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::CrystalCreation()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_monster_creation()
{
	if (_state == ObjectState::MonsterCreation)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::MonsterCreation()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_thrust()
{
	if (_state == ObjectState::Thrust)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Thrust()
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

BehaviorState FinalBoss::is_cur_state_backstep()
{
	if (_state == ObjectState::BackStep)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::BackStep()
{
	if (_dir == DIR_RIGHT)
		_pos.x -= _stat->backStepDistance;
	else
		_pos.x += _stat->backStepDistance;

	SetState(ObjectState::Idle);

	return BehaviorState::SUCCESS;
}

BehaviorState FinalBoss::is_cur_state_slashwave()
{
	if (_state == ObjectState::SlashWave)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::SlashWave()
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

BehaviorState FinalBoss::is_cur_state_dash()
{
	if (_state == ObjectState::Dash)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Dash()
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

BehaviorState FinalBoss::is_cur_state_teleport()
{
	if (_state == ObjectState::Teleport)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Teleport()
{
	// 찌르기 or 마구 베기

	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_cut_severely()
{
	if (_state == ObjectState::CutSeverely)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::CutSeverely()
{
	return BehaviorState();
}

float FinalBoss::GetFromPlayerXDistance()
{
	return this->GetPos().x - _player->GetPos().x;
}

float FinalBoss::GetAbsFromPlayerXDisatance()
{
	return std::abs(GetFromPlayerXDistance());
}

void FinalBoss::SetSpawnPos(Vec2 pos)
{
	_spawnPos = pos;
	SetPos(_spawnPos);
}

void FinalBoss::SetSpawnDir(Dir dir)
{
	_spawnDir = dir;
	SetDir(dir);
}

void FinalBoss::SetMoveDistance(float distance)
{
	_moveDistance = distance;
	_currentMoveDistance = _moveDistance;
}

void FinalBoss::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void FinalBoss::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

void FinalBoss::CreateProjectile()
{
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	std::random_device rd;
	std::mt19937 gen(rd()); // 시드 생성기
	std::uniform_int_distribution<> dist(0, 1); // 0 또는 1 반환

	bool isWType = (dist(gen) == 0);

	if (isWType)
	{
		SlashwaveW* slashwaveW = scene->SpawnObject<SlashwaveW>({ _pos.x, _pos.y }, LAYER_PROJECTILE);
		slashwaveW->SetSpeed(_stat->longAtkProjectileSpeed);
		slashwaveW->SetAttack(_stat->longAtkProjectileDamage);
		slashwaveW->SetRange(_stat->longAtkRange);
		slashwaveW->SetOwner(this);
		slashwaveW->SetDir(_dir);
	}
	else
	{
		SlashwaveH* slashwaveH = scene->SpawnObject<SlashwaveH>({ _pos.x, _pos.y }, LAYER_PROJECTILE);
		slashwaveH->SetSpeed(_stat->longAtkProjectileSpeed);
		slashwaveH->SetAttack(_stat->longAtkProjectileDamage);
		slashwaveH->SetRange(_stat->longAtkRange);
		slashwaveH->SetOwner(this);
		slashwaveH->SetDir(_dir);
	}

	_currentProjectileCount++;
}

void FinalBoss::CreateProjectileFall()
{
}
