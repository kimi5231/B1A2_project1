#include "pch.h"
#include "Slashwave2.h"
#include "DevScene.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "FinalBoss.h"

SlashwaveW::SlashwaveW()
{
	_flipbookW = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SlashwaveW");

	// Collider
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_PROJECTILE);

		collider->SetSize({ 50, 30 });

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	SetState(ObjectState::Move);
}

SlashwaveW::~SlashwaveW()
{
}

void SlashwaveW::BeginPlay()
{
	Super::BeginPlay();
}

void SlashwaveW::Tick()
{
	Super::Tick();
}

void SlashwaveW::Render(HDC hdc)
{
	Super::Render(hdc);
}

float SlashwaveW::GetSpeed()
{
	return 0.0f;
}

void SlashwaveW::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _speed * deltaTime;
	else
		_pos.x -= _speed * deltaTime;

	if (abs(_owner->GetPos().x - _pos.x) >= _range)
	{
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void SlashwaveW::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Move:
		SetFlipbook(_flipbookW);
		break;
	}
}

void SlashwaveW::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void SlashwaveW::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

//////////////////////////////////////////////////////////////////////////

SlashwaveH::SlashwaveH()
{
	_flipbookH = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SlashwaveH");

	// Collider
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_PROJECTILE);

		collider->SetSize({ 20, 90 });

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	SetState(ObjectState::Move);
}

SlashwaveH::~SlashwaveH()
{
}

void SlashwaveH::BeginPlay()
{
	Super::BeginPlay();
}

void SlashwaveH::Tick()
{
	Super::Tick();
}

void SlashwaveH::Render(HDC hdc)
{
	Super::Render(hdc);
}

void SlashwaveH::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _speed * deltaTime;
	else
		_pos.x -= _speed * deltaTime;

	if (abs(_owner->GetPos().x - _pos.x) >= _range)
	{
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void SlashwaveH::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Move:
		SetFlipbook(_flipbookH);
		break;
	}
}

float SlashwaveH::GetSpeed()
{
	return 0.0f;
}

void SlashwaveH::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void SlashwaveH::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
