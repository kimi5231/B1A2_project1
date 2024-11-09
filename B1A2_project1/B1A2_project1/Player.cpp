#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"

// *리소스 마지로 수정해야 함!
Player::Player()
{
	// 젤다
	_flipbookLeft = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveLeft");
	_flipbookRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveRight");

	// 마지
	_flipbookPlayerRunRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerRunRight");
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();

	// 처음 상태 지정
	SetFlipbook(_flipbookRight);
}

void Player::Tick()
{
	Super::Tick();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// *속도 기획 따라 수정하기
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= 200 * deltaTime;
		SetFlipbook(_flipbookLeft);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += 200 * deltaTime;
		SetFlipbook(_flipbookRight);
	}

}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}
