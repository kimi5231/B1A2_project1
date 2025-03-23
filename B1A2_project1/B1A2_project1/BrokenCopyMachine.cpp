#include "pch.h"
#include "BrokenCopyMachine.h"
#include "ResourceManager.h"

BrokenCopyMachine::BrokenCopyMachine()
{
	BrokenCopyMachineStat* brokenCopyMachineStat = new BrokenCopyMachineStat();
	brokenCopyMachineStat = GET_SINGLE(ResourceManager)->LoadBrokenCopyMachineStat(L"DataBase\\brokenCopyMachineStat.csv");
	_stat = brokenCopyMachineStat;

	_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
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
}

void BrokenCopyMachine::TickCloseAttack()
{
}

void BrokenCopyMachine::TickLongAttack()
{
}

void BrokenCopyMachine::TickHit()
{
}

void BrokenCopyMachine::TickDead()
{
}

void BrokenCopyMachine::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		SetFlipbook(_flipbookIdle[_dir]);
		break;
	}
}

int32 BrokenCopyMachine::GetAttack()
{
	return int32();
}