#include "pch.h"
#include "FinalBoss.h"
#include "ResourceManager.h"
#include "BehaviorTree.h"
#include "Player.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "Flipbook.h"

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
	Condition* c5 = new Condition("is cur state Projctile Creation?", [&]() {return is_cur_state_projctile_creation(); });
	Action* a5 = new Action("ProjctileCreation", [&]() {return ProjectileCreation(); });
	Sequence* CrystalCreationSequence = new Sequence();
	CrystalCreationSequence->addChild(c4);
	CrystalCreationSequence->addChild(a4);
	CrystalCreationSequence->addChild(c5);
	CrystalCreationSequence->addChild(a5);

	// Monster Creation Sequeuce
	Condition* c6 = new Condition("is cur state Monster Creation?", [&]() {return is_cur_state_monster_creation(); });
	Action* a6 = new Action("ProjctileCreation", [&]() {return MonsterCreation(); });
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
}

int32 FinalBoss::GetAttack()
{
	return int32();
}

void FinalBoss::CalPixelPerSecond()
{
}

BehaviorState FinalBoss::is_cur_state_idle()
{
	return BehaviorState();
}

BehaviorState FinalBoss::Idle()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_hit()
{
	return BehaviorState();
}

BehaviorState FinalBoss::Hit()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_dead()
{
	return BehaviorState();
}

BehaviorState FinalBoss::Dead()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_projectile_fall()
{
	return BehaviorState();
}

BehaviorState FinalBoss::ProjectileFall()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_projctile_creation()
{
	return BehaviorState();
}

BehaviorState FinalBoss::ProjectileCreation()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_monster_creation()
{
	return BehaviorState();
}

BehaviorState FinalBoss::MonsterCreation()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_thrust()
{
	return BehaviorState();
}

BehaviorState FinalBoss::Thrust()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_backstep()
{
	return BehaviorState();
}

BehaviorState FinalBoss::BackStep()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_slashwave()
{
	return BehaviorState();
}

BehaviorState FinalBoss::SlashWave()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_dash()
{
	return BehaviorState();
}

BehaviorState FinalBoss::Dash()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_teleport()
{
	return BehaviorState();
}

BehaviorState FinalBoss::Teleport()
{
	return BehaviorState();
}

BehaviorState FinalBoss::is_cur_state_cut_severely()
{
	return BehaviorState();
}

BehaviorState FinalBoss::CutSeverely()
{
	return BehaviorState();
}
