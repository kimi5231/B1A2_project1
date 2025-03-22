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

void Creature::OnDamaged(Creature* other)
{
	int32 damage = other->GetAttack();

	if (damage <= 0)
		return;

	int32& hp = GetHp();
	hp = max(0, hp - damage);

	/*if (hp == 0)
	{
		SetState(ObjectState::Dead);
	}

	SetState(ObjectState::Hit);*/
}