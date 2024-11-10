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
	// 마지 리소스
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRunRight", L"Sprite\\Player\\PlayerRunRight.bmp", RGB(55, 255, 0));	// 녹색 배경 (55, 255, 0)
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRunLeft", L"Sprite\\Player\\PlayerRunLeft.bmp", RGB(55, 255, 0));	

	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRunRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerRunRight");
		fb->SetInfo({ texture, L"FB_PlayerRunRight", {67, 70}, 0, 9, 0, 0.7f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRunLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerRunLeft");
		fb->SetInfo({ texture, L"FB_PlayerRunLeft", {67, 70}, 0, 9, 0, 0.7f });
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