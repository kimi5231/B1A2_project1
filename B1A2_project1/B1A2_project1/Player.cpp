#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "CameraComponent.h"
#include "DialogueComponent.h"
#include "Dialogue.h"
#include "Game.h"
#include "BoxCollider.h"
#include "ItemActor.h"
#include "Item.h"

Player::Player()
{
	// PlayerStat
	PlayerStat* playerStat = new PlayerStat();
	playerStat = GET_SINGLE(ResourceManager)->LoadPlayerStat(L"DataBase\\playerStat.csv");
	_playerStat = playerStat;
	CalPixelPerSecond();
	
	// 마지
	_flipbookPlayerMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerMoveRight");
	_flipbookPlayerMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerMoveLeft");

	// 카메라 컴포넌트
	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);

	// Dialogue Component
	DialogueComponent* dialogueComponent = new DialogueComponent();
	AddComponent(dialogueComponent);
}

Player::~Player()
{
}

void Player::BeginPlay()
{	
	Super::BeginPlay();

	// 처음 상태 지정
	SetState(PlayerState::Idle);
}

void Player::Tick()
{
	Super::Tick();

	// 대화 중에는 조작할 수 없도록 상태 변화 스킵
	// 이 코드의 위치는 추후 수정될 수 있음
	if (GetDialogue()->GetState() == DialogueState::Running || GetDialogue()->GetState() == DialogueState::Wait)
		return;


	// Item 획득
	if (_collideItem)
	{
		if (_collideItem->GetFKeyState() == FKeyState::Show)
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::F))
			{
				_acquiredItems[_collideItem->GetItemID()]++;
			}
		}
	}


	switch (_state)
	{
	case PlayerState::Idle:
		TickIdle();
		break;
	case PlayerState::Move:
		TickMove();
		break;
	//case PlayerState::DuckDown:
	//	TickDuckDown();
	//	break;
	case PlayerState::Jump:
		TickJump();
		break;
	//case PlayerState::Hang:
	//	TickHang();
	//	break;
	//case PlayerState::Release:
	//	TickRelease();
	//	break;
	//case PlayerState::Skill:
	//	TickSkill();
	//	break;
	//case PlayerState::AttackNormal:
	//	TickAttackNormal();
	//	break;
	//case PlayerState::Hit:
	//	TickHit();
	//	break;
	//case PlayerState::Dead:
	//	TickDead();
	//	break;
	}

	//TickGravity();
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::CalPixelPerSecond()
{
	float PIXEL_PER_METER = (10.0 / 0.3);
		
	// run
	float RUN_SPEED_KMPH = _playerStat->runSpeed;
	float RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0);
	float RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0);
	float RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER);

	// crouch
	float CROUCH_SPEED_KMPH = _playerStat->crouchSpeed;
	float CROUCH_SPEED_MPM = (CROUCH_SPEED_KMPH * 1000.0 / 60.0);
	float CROUCH_SPEED_MPS = (CROUCH_SPEED_MPM / 60.0);
	float CROUCH_SPEED_PPS = (CROUCH_SPEED_MPS * PIXEL_PER_METER);

	_playerStat->runSpeed = RUN_SPEED_PPS;
	_playerStat->crouchSpeed = CROUCH_SPEED_PPS;
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
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		if (_Ground)	// 충돌 체크에서 땅에 닿으면 _Ground = true로 됐는데 왜 false로 나오는 거지??
		{
			SetState(PlayerState::Jump);
		}
		return;
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

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
		_pos.x -= _playerStat->runSpeed * deltaTime;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		_pos.x += _playerStat->runSpeed * deltaTime;
	}
	//switch (_dir)		// 이 코드로 하면 키보드 입력이 한 번밖에 안 먹음.. 일단 보류
	//{
	//case DIR_RIGHT:
	//	_pos.x += 200 * deltaTime;
	//	break;
	//case DIR_LEFT:
	//	_pos.x -= 200 * deltaTime;
	//	break;
	//}
}

void Player::TickDuckDown()
{
}

void Player::TickDuckDownMove()
{
}

void Player::TickJump()
{
	//if (_isInAir)
	//	return;

	//if (_Ground)
	//	SetState(PlayerState::Idle);

	//_isInAir = true;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();


	if (deltaTime > 0.1f)
		return;
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
			SetFlipbook(_flipbookPlayerMove[_dir]);		// IDLE 리소스 없어서, 리소스 생기면 Idle로 바꾸기
		break;
	case PlayerState::Move:
		SetFlipbook(_flipbookPlayerMove[_dir]);
		break;
	//case PlayerState::DuckDown:
	//	SetFlipbook(_flipbookPlayerDuckDown[_dir]);
	//	break;
	//case PlayerState::DuckDownMove:
	//	SetFlipbook(_flipbookPlayerDuckDownMove[_dir]);
	//	break;
	case PlayerState::Jump:
		SetFlipbook(_flipbookPlayerMove[_dir]);
		break;
	//case PlayerState::Hang:
	//	SetFlipbook(_flipbookPlayerHang[_dir]);
	//	break;
	//case PlayerState::Release:
	//	SetFlipbook(_flipbookPlayerRelease[_dir]);
	//	break;
	//case PlayerState::Skill:
	//	SetFlipbook(_flipbookPlayerSkill[_dir]);
	//	break;
	//case PlayerState::AttackNormal:
	//	SetFlipbook(_flipbookPlayerAttackNormal[_dir]);
	//	break;
	//case PlayerState::Hit:
	//	SetFlipbook(_flipbookPlayerHit[_dir]);
	//	break;
	//case PlayerState::Dead:
	//	SetFlipbook(_flipbookPlayerDead[_dir]);
	//	break;
	}
}

void Player::TickGravity()
{
	// 땅에 닿아있으면 중력 적용 X
	if (_Ground)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	if (deltaTime > 0.1f)
		return;

	// v = at
	// s = vt

	_ySpeed += _gravity * deltaTime;
	_pos.y += _ySpeed * deltaTime;
}


void Player::RemoveItem(int32 id, int32 count)
{
	if (_acquiredItems.find(id) != _acquiredItems.end() && _acquiredItems[id] >= count)
	{
		_acquiredItems[id] -= count;
		if (_acquiredItems[id] == 0)	// 아이템 개수가 0이면 삭제
			_acquiredItems.erase(id);	
	}
}

void Player::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_ITEM)
	{
		ItemActor* item = reinterpret_cast<ItemActor*>(b2->GetOwner());
		item->SetFKeyState(FKeyState::Show);

		_collideItem = item;

		return;
	}

	AdjustCollisionPos(b1, b2);

	// 충돌 시작 : 땅에 닿음
	if (b2->GetCollisionLayer() == CLT_GROUND)
		_Ground = true;
}

void Player::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_ITEM)
	{
		ItemActor* Item = reinterpret_cast<ItemActor*>(b2->GetOwner());
		Item->SetFKeyState(FKeyState::Hidden);

		_collideItem = nullptr;

		return;
	}

	// 충돌 끝: 땅에서 떨어짐
	//if (b2->GetCollisionLayer() == CLT_GROUND)
	//	_Ground = false;
}

void Player::AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	Vec2 pos = GetPos();

	RECT intersect = {};	// 충돌된 범위
	if (::IntersectRect(&intersect, &r1, &r2))
	{
		int32 w = intersect.right - intersect.left;
		int32 h = intersect.bottom - intersect.top;
		
		if (w > h)
		{
			if (intersect.top == r2.top)
			{
				// 위로 올려 보내기
				pos.y -= h;
			}
			else
			{
				// 아래로 내려 보내기
				pos.x += h;
			}
		}
		else
		{
			if (intersect.left == r2.left)
			{
				pos.x -= w;
			}
			else
			{
				pos.x += w;
			}
		}
	}
	
	SetPos(pos);
}
