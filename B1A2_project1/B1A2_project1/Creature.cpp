#include "pch.h"
#include "Creature.h"

Creature::Creature()
{
}

Creature::~Creature()
{
}

void Creature::BeginPlay()
{
	Super::BeginPlay();
}

void Creature::Tick()
{
	Super::Tick();
}

void Creature::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Creature::OnDameged(int32 damage)
{
	CommonStat& stat = GetCommonStat();

	if (damage <= 0)
		return;

	stat.hp = max(0, stat.hp - damage);

	if (stat.hp == 0)
	{
		SetState(ObjectState::Dead);
	}

	SetState(ObjectState::Hit);
}
