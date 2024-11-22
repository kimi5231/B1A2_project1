#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "CameraComponent.h"

Player::Player()
{
	// 마지
	_flipbookPlayerMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerRunRight");
	_flipbookPlayerMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerRunLeft");

	// 카메라 컴포넌트
	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);
}

Player::~Player()
{
}

void Player::BeginPlay()
{	
	Super::BeginPlay();

	// 처음 상태 지정
	// SetFlipbook(_flipbookPlayerRunRight);
	SetState(PlayerState::Idle);
	
}

void Player::Tick()
{
	Super::Tick();

	switch (_state)
	{
	case PlayerState::Idle:
		TickIdle();
		break;
	case PlayerState::Move:
		TickMove();
		break;
	case PlayerState::DuckDown:
		TickDuckDown();
		break;
	case PlayerState::Jump:
		TickJump();
		break;
	case PlayerState::Hang:
		TickHang();
		break;
	case PlayerState::Release:
		TickRelease();
		break;
	case PlayerState::Skill:
		TickSkill();
		break;
	case PlayerState::AttackNormal:
		TickAttackNormal();
		break;
	case PlayerState::Hit:
		TickHit();
		break;
	case PlayerState::Dead:
		TickDead();
		break;
	}

}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::TickIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	
	_keyPressed = true;

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
		SetState(PlayerState::Move);
		
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		SetState(PlayerState::Move);
	}
	else
	{
		_keyPressed = false;
		if (_state == PlayerState::Idle)
			UpdateAnimation();
	}
}

void Player::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	switch (_dir)
	{
	case DIR_RIGHT:
		_pos.x += 200 * deltaTime;
		break;
	case DIR_LEFT:
		_pos.x -= 200 * deltaTime;
		break;
	}
}

void Player::TickDuckDown()
{
}

void Player::TickJump()
{
}

void Player::TickHang()
{
}

void Player::TickRelease()
{
}

void Player::TickSkill()
{
}

void Player::TickAttackNormal()
{
}

void Player::TickHit()
{
}

void Player::TickDead()
{
}


void Player::SetState(PlayerState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void Player::SetDir(Dir dir)
{
	_dir = dir;
	UpdateAnimation();
}

void Player::UpdateAnimation()
{
	switch (_state)
	{
	case PlayerState::Idle:
		if (_keyPressed)
			SetFlipbook(_flipbookPlayerMove[_dir]);
		else
			SetFlipbook(_flipbookPlayerIdle[_dir]);
		break;
	case PlayerState::Move:
		SetFlipbook(_flipbookPlayerMove[_dir]);
		break;
	case PlayerState::DuckDown:
		SetFlipbook(_flipbookPlayerDuckDown[_dir]);
		break;

	}
}
