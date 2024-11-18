#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "CameraComponent.h"

Player::Player()
{
	// 마지
	_flipbookPlayerRunRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerRunRight");
	_flipbookPlayerRunLeft = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerRunLeft");

	// 카메라 컴포넌트
	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	// 처음 상태 지정
	SetFlipbook(_flipbookPlayerRunRight);

	Super::BeginPlay();
}

void Player::Tick()
{
	Super::Tick();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// *속도 기획 따라 수정하기
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= 200 * deltaTime;
		SetFlipbook(_flipbookPlayerRunLeft);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += 200 * deltaTime;
		SetFlipbook(_flipbookPlayerRunRight);
	}
	
	// 타일맵 찍기 위해 위아래 움직임 추가
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		_pos.y -= 200 * deltaTime;
		SetFlipbook(_flipbookPlayerRunRight);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_pos.y += 200 * deltaTime;
		SetFlipbook(_flipbookPlayerRunRight);
	}
	//
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::TickIdle()
{
}

void Player::TickMove()
{
}

void Player::TickSkill()
{
}

void Player::SetState(PlayerState)
{
}

void Player::UpdateAnimation()
{
}
