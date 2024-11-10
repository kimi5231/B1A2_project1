#include "pch.h"
#include "DevScene.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Texture.h"
#include "Flipbook.h"
#include "Sprite.h"
#include "SpriteActor.h"
#include "Actor.h"
#include "Flipbook.h"
#include "Player.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	// 젤다 리소스
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));

	// 마지 리소스
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRunRight", L"Sprite\\Player\\PlayerRun.bmp", RGB(55, 255, 128));	// 녹색 배경 (55, 255, 0)

	// IDLE
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleLeft");
		fb->SetInfo({ texture, L"FB_MoveLeft", {200, 200}, 0, 9, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleRight");
		fb->SetInfo({ texture, L"FB_MoveRight", {200, 200}, 0, 9, 0, 0.5f });
	}
	// MOVE
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft");
		fb->SetInfo({ texture, L"FB_MoveLeft", {200, 200}, 0, 9, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight");
		fb->SetInfo({ texture, L"FB_MoveRight", {200, 200}, 0, 9, 1, 0.5f });
	}

	{
		Player* player = new Player();
		_actor = player;
	}

	Super::Init();
}

void DevScene::Update()
{
	Super::Update(); 

	_actor->Tick();
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);

	_actor->Render(hdc);
}