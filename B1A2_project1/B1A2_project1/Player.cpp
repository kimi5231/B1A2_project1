#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "ValueManager.h"
#include "DialogueManager.h"
#include "CameraComponent.h"
#include "DialogueComponent.h"
#include "Dialogue.h"
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
	
	// Flipbook Sprite
	_flipbookPlayerIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerIdleRight");
	_flipbookPlayerIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerIdleLeft");
	_flipbookPlayerMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerMoveRight");
	_flipbookPlayerMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerMoveLeft");

	// Camera Component
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
}

void Player::Tick()
{
	Super::Tick();

	// 대화 중에는 조작할 수 없도록 상태 변화 스킵
	// 이 코드의 위치는 추후 수정될 수 있음
	if (GET_SINGLE(DialogueManager)->GetIsDialouge())
		return;
	/*if (GetDialogue()->GetState() == DialogueState::Running || GetDialogue()->GetState() == DialogueState::Wait)
		return;*/

	// F key가 활성화되면 획득할 수 있음
	// 획득 후 F key와 Item을 화면에서 지움
	if (_collideItem)
	{
		if (_collideItem->GetFKeyState() == FKeyState::Show)
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::F))
			{
				_acquiredItems[_collideItem->GetItemID()]++;
				
				Collider* collider = _collideItem->GetCollider();
				if (collider)
				{
					collider->SetCollisionLayer(CLT_NONE);
				}
			
				_collideItem->SetFKeyState(FKeyState::Hidden);
				_collideItem->SetItemState(ItemState::Hidden);
			}
		}
	}

	TickGravity();

	// 플레이어가 화면 밖으로 넘어가지 않도록
	Vec2Int mapSize = GET_SINGLE(ValueManager)->GetMapSize();
	_pos.x = std::clamp(_pos.x, (float)(67 / 2), (float)mapSize.x);		// 67은 DevScene에서 설정한 Player collider 크기
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::TickIdle()
{
	if (GetDialogue()->GetState() == DialogueState::Running || GetDialogue()->GetState() == DialogueState::Wait)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	
	_keyPressed = true;

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
		SetState(ObjectState::Move);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		SetState(ObjectState::Move);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// 이미 점프 중이면 리턴
		if (!_isGround && _isAir)
			return;

		SubtractHealthPoint(3);		// 체력바 test

		_isGround = false;
		_isAir = true;

		SetState(ObjectState::Jump);

		_ySpeed = -_playerStat->jumpSpeed;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		SetState(ObjectState::DuckDown);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		SetState(ObjectState::NormalAttack);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))
	{
		SetState(ObjectState::Skill);
	}
	else
	{
		_keyPressed = false;

		if (_state == ObjectState::Idle)
			UpdateAnimation();
	}
	
	//if (공격 받음)
	//{
	//	SubtractHealthPoint(깎을hp);
	//	SetState(ObjectState::Hit);
	//}
}

void Player::TickMove()
{
	if (GetDialogue()->GetState() == DialogueState::Running || GetDialogue()->GetState() == DialogueState::Wait)
		return;

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
	else
	{
		SetState(ObjectState::Idle); // 이동 키를 뗐을 때 Idle 상태로 변경
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// 이미 점프 중이면 리턴
		if (!_isGround && _isAir)
			return;

		_isGround = false;
		_isAir = true;

		SetState(ObjectState::Jump);

		_ySpeed = -_playerStat->jumpSpeed;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		SetState(ObjectState::DuckDownMove);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))	// Normal Attack
	{
		SetState(ObjectState::NormalAttack);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))	// Skill
	{
		SetState(ObjectState::Skill);
	}

	//if (공격 받음)
	//{
	//	SubtractHealthPoint(깎을hp);
	//	SetState(ObjectState::Hit);
	//}
}

void Player::TickDuckDown()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::A))
	{
		SetDir(DIR_LEFT);
		SetState(ObjectState::DuckDownMove);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		SetState(ObjectState::DuckDownMove);
	}
	else if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::S))	// 버튼을 뗐을 때
	{
		SetState(ObjectState::Idle);
	}

	//if (공격 받음)
	//{
	//	SubtractHealthPoint(깎을hp);
	//	SetState(ObjectState::Hit);
	//}

}

void Player::TickDuckDownMove()
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
	
	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::A) || GET_SINGLE(InputManager)->GetButtonUp(KeyType::D))
	{
		SetState(ObjectState::DuckDown);
	}

	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::S))
	{
		SetState(ObjectState::Move);
	}

	//if (공격 받음)
	//{
	//	SubtractHealthPoint(깎을hp);
	//	SetState(ObjectState::Hit);
	//}

}

void Player::TickJump()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 좌우 이동도 가능하도록 추가
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

	if (_isGround && !_isAir)	// 땅에 닿았을 때
	{
		if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
		{
			SetDir(DIR_LEFT);
			SetState(ObjectState::Move);
		}
		else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
		{
			SetDir(DIR_RIGHT);
			SetState(ObjectState::Move);
		}
		else
			SetState(ObjectState::Idle);
	}

	//if (공격 받음)
	//{
	//	SubtractHealthPoint(깎을hp);
	//	SetState(ObjectState::Hit);
	//}

 }

void Player::TickNormalAttack()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 좌우 이동도 가능하도록 추가
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

	//if (공격 받음)
	//{
	//	SubtractHealthPoint(깎을hp);
	//	SetState(ObjectState::Hit);
	//}

	// 공격 코드 작성
	// ...

	SetState(ObjectState::Idle);
}

void Player::TickSkill()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 좌우 이동도 가능하도록 추가
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

	//if (공격 받음)
	//{
	//	SubtractHealthPoint(깎을hp);
	//	SetState(ObjectState::Hit);
	//}

	// 스킬 코드 작성
	// ...

	SetState(ObjectState::Idle);
}

void Player::TickHang()
{
}

void Player::TickRelease()
{
}

void Player::TickHit()
{
	// 피격 코드 작성
	// ...

	if (_playerStat->healthPoint > 0)
		SetState(ObjectState::Idle);
	else
		SetState(ObjectState::Dead);
}

void Player::TickDead()
{
	// 죽는 코드 작성
	// ...
}

void Player::UpdateAnimation()
{
	BoxCollider* playerCollider = dynamic_cast<BoxCollider*>(this->GetCollider());

	switch (_state)
	{
	case ObjectState::Idle:
		playerCollider->SetSize({ 23, 85 });
		if (_keyPressed)
			SetFlipbook(_flipbookPlayerIdle[_dir]);
		else
			SetFlipbook(_flipbookPlayerIdle[_dir]);		
		break;
	case ObjectState::Move:
		playerCollider->SetSize({67, 70 });
		SetFlipbook(_flipbookPlayerMove[_dir]);
		break;
	case ObjectState::DuckDown:
		playerCollider->SetSize({67, 40});
		//SetFlipbook(_flipbookPlayerDuckDown[_dir]);
		break;
	case ObjectState::DuckDownMove:
		playerCollider->SetSize({ 67, 40 });
		//SetFlipbook(_flipbookPlayerDuckDownMove[_dir]);
		break;
	case ObjectState::Jump:
		playerCollider->SetSize({ 34, 55 });
		SetFlipbook(_flipbookPlayerMove[_dir]);
		break;
	//case ObjectState::Hang:
	//	SetFlipbook(_flipbookPlayerHang[_dir]);
	//	break;
	//case ObjectState::Release:
	//	SetFlipbook(_flipbookPlayerRelease[_dir]);
	//	break;
	case ObjectState::Skill:
		//playerCollider->SetSize({})
		//SetFlipbook(_flipbookPlayerSkill[_dir]);
		break;
	case ObjectState::NormalAttack:
		//playerCollider->SetSize({})
		//SetFlipbook(_flipbookPlayerAttackNormal[_dir]);
		break;
	case ObjectState::Hit:
	//	SetFlipbook(_flipbookPlayerHit[_dir]);
	break;
	case ObjectState::Dead:
	//	SetFlipbook(_flipbookPlayerDead[_dir]);
	break;
	}
}

void Player::AddHealthPoint(int hp)
{
	if (_playerStat->healthPoint >= 100)
		return;

	_playerStat->healthPoint += hp;

	// 관찰자에게 알림
	_healthObserver(_playerStat->healthPoint);
}

void Player::SubtractHealthPoint(int hp)
{
	if (_playerStat->healthPoint <= 0)
		return;

	_playerStat->healthPoint -= hp;

	// 관찰자에게 알림
	_healthObserver(_playerStat->healthPoint);
}

void Player::CalPixelPerSecond()
{
	float PIXEL_PER_METER = (10.0 / 0.3);

	// run
	{
		float RUN_SPEED_KMPH = _playerStat->runSpeed;
		float RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0);
		float RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0);
		float RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER);

		_playerStat->runSpeed = RUN_SPEED_PPS;
	}

	// crouch
	{
		float CROUCH_SPEED_KMPH = _playerStat->crouchSpeed;
		float CROUCH_SPEED_MPM = (CROUCH_SPEED_KMPH * 1000.0 / 60.0);
		float CROUCH_SPEED_MPS = (CROUCH_SPEED_MPM / 60.0);
		float CROUCH_SPEED_PPS = (CROUCH_SPEED_MPS * PIXEL_PER_METER);

		_playerStat->crouchSpeed = CROUCH_SPEED_PPS;
	}

	// jump
	{
		float JUMP_SPEED_KMPH = _playerStat->jumpSpeed;
		float JUMP_SPEED_MPM = (JUMP_SPEED_KMPH * 1000.0 / 60.0);
		float JUMP_SPEED_MPS = (JUMP_SPEED_MPM / 60.0);
		float JUMP_SPEED_PPS = (JUMP_SPEED_MPS * PIXEL_PER_METER);

		_playerStat->jumpSpeed = JUMP_SPEED_PPS;
	}

}

void Player::TickGravity()
{
	// 땅에 닿아있으면 중력 적용 X
	if (_isGround)
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

	// Item과 충돌하면 F key 활성화(밀어내기 X)
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
	{
		_groundCollisionCount++;
		_isGround = true;
		_isAir = false;
	}
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

	if (b2->GetCollisionLayer() == CLT_GROUND)
	{
		_groundCollisionCount--;

		if (_groundCollisionCount <= 0)		// 충돌 끝: 땅에서 떨어짐
		{
			_isGround = false;
			_isAir = true;
			_groundCollisionCount = 0;
		}
	}
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