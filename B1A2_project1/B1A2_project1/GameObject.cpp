#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::BeginPlay()
{
	Super::BeginPlay();
}

void GameObject::Tick()
{
	Super::Tick();

	switch (_state)
	{
	case ObjectState::Idle:
		TickIdle();
		break;
	case ObjectState::Move:
		TickMove();
		break;
	case ObjectState::DuckDown:
		TickDuckDown();
		break;
	case ObjectState::DuckDownMove:
		TickDuckDownMove();
		break;
	case ObjectState::Jump:
		TickJump();
		break;
	case ObjectState::NormalAttack:
		TickNormalAttack();
		break;
	case ObjectState::Skill:
		TickSkill();
		break;
	case ObjectState::Hang:
		TickHang();
		break;
	case ObjectState::Release:
		TickRelease();
		break;
	case ObjectState::Hit:
		TickHit();
		break;
	case ObjectState::Dead:
		TickDead();
		break;
	}
}

void GameObject::Render(HDC hdc)
{
	Super::Render(hdc);
}

void GameObject::SetState(ObjectState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void GameObject::SetDir(Dir dir)
{
	_dir = dir;
	UpdateAnimation();
}