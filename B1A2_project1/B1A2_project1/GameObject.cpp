#include "pch.h"
#include "GameObject.h"
#include "DialogueManager.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::BeginPlay()
{
	Super::BeginPlay();

	// 처음 상태 지정
	SetState(ObjectState::Dead);
	SetState(ObjectState::Idle);
}

void GameObject::Tick()
{
	Super::Tick();

	if (GET_SINGLE(DialogueManager)->GetIsDialouge())
		return;

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
	case ObjectState::Chase:
		TickChase();
		break;
	case ObjectState::Roaming:
		TickRoaming();
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