#include "pch.h"
#include "AmateurFencer.h"
#include "BehaviorTree.h"
#include "Player.h"
#include "ResourceManager.h"

AmateurFencer::AmateurFencer()
{
	// Stat
	AmateurFencerStat* amateurFencerStat = new AmateurFencerStat();
	amateurFencerStat = GET_SINGLE(ResourceManager)->LoadAmateurFencerStat(L"DataBase\\amateurFencerStat.csv");
	_stat = amateurFencerStat;

	// Flipbook
	_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencer");

	//_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerIdle");
	//_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerIdle");
	//_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerHitRight");
	//_flipbookHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerHitLeft");
	//_flipbookChase[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerChaseRight");
	//_flipbookChase[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerChaseLeft");
	//_flipbookCloseAtk[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerCloseAtkRight");
	//_flipbookCloseAtk[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerCloseAtkLeft");
	//_flipbookLongAtk[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerLongAtkRight");
	//_flipbookLongAtk[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerLongAtkLeft");
	//_flipbookDash[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerDashRight");
	//_flipbookDash[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerDashLeft");
	//_flipbookDie[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerDieRight");
	//_flipbookDie[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AmateurFencerDieLeft");
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
	//Super::Tick();

	if (_rootNode)
	{
		_rootNode->run();
	}
}

void AmateurFencer::Render(HDC hdc)
{
	Super::Render(hdc);
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
	// 플립북 변경
	// ...

	// 수정 필요(플레이어와의 거리)
	int distance = 0;

	if (distance <= 320)
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
	// 플립북 변경
	// ...

	//if (attacked 플립북이 끝남)
	//{
	//	if (_commonStat.hp <= 0)
	//	{
	//		_state = ObjectState::Dead;
	//		// 죽는 애니메이션 플립북 1번 재생 후
	//		// 소멸시키기
	//	}
	//	_state = ObjectState::Idle;
	//	return BehaviorState::SUCCESS;
	//}
	//else
	//	return BehaviorState::RUNNING;

	return BehaviorState();
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
	// 수정 필요(플레이어와의 거리)
	int distance = 0;

	if (distance > 120 && distance <= 320)
	{
		// 쫓아가는 코드
		return BehaviorState::RUNNING;
	}
	else if (distance <= 120)
	{
		_state = ObjectState::CloseAttack;
		return BehaviorState::SUCCESS;
	}
	/*else if (std::abs(distance - 근.공.사) > std::abs(distance - 원.공.사))
	{
		_state = ObjectState::LongAttack;
		return BehaviorState::SUCCESS;
	}*/
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
	// 수정 필요(플레이어와의 거리)
	int distance = 0;

	if (distance <= 120)
	{
		// 근거리 공격 코드
		return BehaviorState::RUNNING;
	}
	else if (distance > 120 && distance <= 320)
	{
		_state = ObjectState::CloseAttack;
		return BehaviorState::SUCCESS;
	}
	/*else if (std::abs(distance - 근.공.사) > std::abs(distance - 원.공.사))
	{
		_state = ObjectState::LongAttack;
		return BehaviorState::SUCCESS;
	}*/
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
	// 수정 필요(플레이어와의 거리)
	int distance = 0;

	//if (std::abs(distance - 근.공.사) > std::abs(distance - 원.공.사))
	//{
	//	원거리 공격 코드	
	//	return BehaviorState::RUNNING;
	//}
	if (distance <= 120)
	{
		_state = ObjectState::CloseAttack;
		return BehaviorState::SUCCESS;
	}
	else if (distance > 120 && distance <= 320)
	{
		_state = ObjectState::Chase;
		return BehaviorState::SUCCESS;
	}

	// 수정 필요
	return BehaviorState();
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
	// Dash 애니메이션 한 번 재생 후

	_state = ObjectState::Chase;	// 변경할 수도!?

	// 수정 필요
	return BehaviorState();
}

void AmateurFencer::UpdateAnimation()
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
