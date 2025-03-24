#include "pch.h"
#include "SlashWave.h"
#include "DevScene.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

SlashWave::SlashWave()
{
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SlashWave");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SlashWave");
	
	// Collider Component
	{
		// Projectile
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_PROJECTILE);

			collider->SetSize({ 20, 88 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}

	SetState(ObjectState::Move);
}

SlashWave::~SlashWave()
{
}

void SlashWave::BeginPlay()
{
	Super::BeginPlay();
}

void SlashWave::Tick()
{
	Super::Tick();
}

void SlashWave::Render(HDC hdc)
{
	Super::Render(hdc);
}

void SlashWave::TickMove()
{
}

void SlashWave::UpdateAnimation()
{
}

void SlashWave::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void SlashWave::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
