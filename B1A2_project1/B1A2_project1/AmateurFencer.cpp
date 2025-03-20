#include "pch.h"
#include "AmateurFencer.h"
#include "BehaviorTree.h"
#include "Player.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "BoxCollider.h"
#include "Flipbook.h"
#include "TimeManager.h"

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
	_flipbookCloseAtk[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookCloseAtk[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookLongAtk[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookLongAtk[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookDash[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookDash[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookDie[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookDie[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");

	/*_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerIdle");
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerIdle");
	_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerHitRight");
	_flipbookHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerHitLeft");
	_flipbookChase[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerChaseRight");
	_flipbookChase[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerChaseLeft");
	_flipbookCloseAtk[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerCloseAtkRight");
	_flipbookCloseAtk[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerCloseAtkLeft");
	_flipbookLongAtk[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerLongAtkRight");
	_flipbookLongAtk[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerLongAtkLeft");
	_flipbookDash[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerDashRight");
	_flipbookDash[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerDashLeft");
	_flipbookDie[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerDieRight");
	_flipbookDie[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerDieLeft");*/

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
	Condition* c3 = new Condition("is cur State Chase?", [&]() {return is_cur_state_chase(); });
	Action* a3 = new Action("Chase", [&]() {return Chase(); });
	Sequence* ChaseSequence = new Sequence();
	ChaseSequence->addChild(c3);
	ChaseSequence->addChild(a3);

	// Attack Selector
	// Close Atk Sequence
	Condition* c4 = new Condition("is cur State CloseAtk?", [&]() {return is_cur_state_close_atk(); });
	Action* a4 = new Action("CloseAtk", [&]() {return Close_atk(); });
	Sequence* CloseAtkSequence = new Sequence();
	CloseAtkSequence->addChild(c4);
	CloseAtkSequence->addChild(a4);
	
	// Long Atk Sequence
	Condition* c5 = new Condition("is cur State LongAtk?", [&]() {return is_cur_state_long_atk(); });
	Action* a5 = new Action("CloseAtk", [&]() {return Long_atk(); });
	
	// Dash Sequence
	Condition* c6 = new Condition("is cur State Dash?", [&]() {return is_cur_state_dash(); });
	Action* a6 = new Action("Dash", [&]() {return Dash(); });
	Sequence* DashSequence = new Sequence();
	DashSequence->addChild(c4);
	DashSequence->addChild(a4);
	
	Sequence* LongAtkSequence = new Sequence();
	LongAtkSequence->addChild(c5);
	LongAtkSequence->addChild(a5);
	LongAtkSequence->addChild(DashSequence);

	Selector* AttackSelector = new Selector();
	AttackSelector->addChild(CloseAtkSequence);
	AttackSelector->addChild(LongAtkSequence);

	// rootNode 설정
	Selector* RootSelector = new Selector();
	RootSelector->addChild(IdleSequence);
	RootSelector->addChild(HitSequence);
	RootSelector->addChild(ChaseSequence);
	RootSelector->addChild(AttackSelector);
	_rootNode = RootSelector;
}

void AmateurFencer::Tick()
{
	Super::Tick();

	if (GetFromPlayerXDistance() >= 0)
		SetDir(DIR_LEFT);
	else
		SetDir(DIR_RIGHT);

	if (_rootNode)
	{
		_rootNode->run();
	}
}

void AmateurFencer::Render(HDC hdc)
{
	Super::Render(hdc);
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
	SetFlipbook(_flipbookIdle[_dir]);

	if (std::abs(GetFromPlayerXDistance()) <= 320.f)
	{
		_state = ObjectState::LongAttack;
		return BehaviorState::SUCCESS;
	}

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
	SetFlipbook(_flipbookHit[_dir]);

	if (this->GetIdx() == _flipbookHit[_dir]->GetFlipbookEndNum())
	{
		if (_commonStat.hp <= 0)
			_state = ObjectState::Dead;
		else
			_state = ObjectState::Idle;

		return BehaviorState::SUCCESS;
	}
	else
		return BehaviorState::RUNNING;
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

	SetFlipbook(_flipbookChase[_dir]);

	if (GetAbsFromPlayerXDisatance() > 120 && GetAbsFromPlayerXDisatance() <= 320)
	{
		if (_dir == DIR_RIGHT)
			_pos.x += _stat->speed * deltaTime;
		else
			_pos.x -= _stat->speed * deltaTime;

		return BehaviorState::RUNNING;
	}
	//else if (GetAbsFromPlayerXDisatance() <= 120)
	//{
	//	_state = ObjectState::CloseAttack;
	//	return BehaviorState::SUCCESS;
	//}
	//else if (std::abs(GetAbsFromPlayerXDisatance() - _stat->closeAtkRange) > std::abs(GetAbsFromPlayerXDisatance() - _stat->longAtkRange))	// |거리 - 근공사| > |거리 - 원공사| 
	//{
	//	_state = ObjectState::LongAttack;
	//	return BehaviorState::SUCCESS;
	//}
}

BehaviorState AmateurFencer::is_cur_state_close_atk()
{
	if (_state == ObjectState::CloseAttack)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Close_atk()
{
	SetFlipbook(_flipbookCloseAtk[_dir]);

	if (GetAbsFromPlayerXDisatance() <= 120)
	{
		// 근거리 공격 코드 작성
		// ...

		return BehaviorState::RUNNING;
	}
	else if (GetAbsFromPlayerXDisatance() > 120 && GetAbsFromPlayerXDisatance() <= 320)
	{
		_state = ObjectState::CloseAttack;
		return BehaviorState::SUCCESS;
	}
	else if (std::abs(GetAbsFromPlayerXDisatance() - _stat->closeAtkDamage) > std::abs(GetAbsFromPlayerXDisatance() - _stat->longAtkRange))
	{
		_state = ObjectState::LongAttack;
		return BehaviorState::SUCCESS;
	}
}

BehaviorState AmateurFencer::is_cur_state_long_atk()
{
	if (_state == ObjectState::LongAttack)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState AmateurFencer::Long_atk()
{
	SetFlipbook(_flipbookLongAtk[_dir]);

	if (std::abs(GetAbsFromPlayerXDisatance() - _stat->closeAtkDamage) > std::abs(GetAbsFromPlayerXDisatance() - _stat->longAtkRange))
	{
		// 원거리 공격 코드 작성
		// ...

		return BehaviorState::RUNNING;
	}

	if (GetAbsFromPlayerXDisatance() <= 120)
	{
		_state = ObjectState::CloseAttack;
		return BehaviorState::SUCCESS;
	}
	else if (GetAbsFromPlayerXDisatance() > 120 && GetAbsFromPlayerXDisatance() <= 320)
	{
		_state = ObjectState::Chase;
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
	SetFlipbook(_flipbookDash[_dir]);

	if (this->GetIdx() == _flipbookDash[_dir]->GetFlipbookEndNum())		// Dash 애니메이션 한 번 재생
	{
		_state = ObjectState::Chase;	// 변경할 수도??

		return BehaviorState::SUCCESS;
	}
	
	return BehaviorState::RUNNING;
}

float AmateurFencer::GetFromPlayerXDistance()
{
	return this->GetPos().x - _player->GetPos().x;	// 양수 → 플레이어보다 오른쪽에, 음수 → 플레이어보다 왼쪽에
}

float AmateurFencer::GetAbsFromPlayerXDisatance()
{
	return std::abs(GetFromPlayerXDistance());
}
