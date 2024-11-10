#include "pch.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteActor.h"
#include "Flipbook.h"
#include "Player.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
	// Load Texture
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));

	// Create Sprite
	GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));

	// Player - IDLE
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

	// Player - MOVE
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
	
	// Background
	//{
	//	Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");
	//	SpriteActor* background = new SpriteActor();
	//	background->SetSprite(sprite);
	//	background->SetPos(Vec2(0, 0));		// 포지션 지정

	//	_background = background;
	//}

	// Player
	{
		Player* player = new Player();
		_actor = player;
	}
	/*{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		const Vec2Int size = sprite->GetSize();
		background->SetPos(Vec2(size.x / 2, size.y / 2));

		AddActor(background);
	}*/

	Super::Init();
}

void TestScene::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// _background->Tick();
	_actor->Tick();
}

void TestScene::Render(HDC hdc)
{
	Super::Render(hdc);

	//Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Stage01");
	//Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Start_On");

	//::BitBlt(hdc,
	//	0, 0,	// 시작하는 위치 (0, 0)
	//	GWinSizeX, GWinSizeY,
	//	sprite->GetDC(),
	//	sprite->GetPos().x, sprite->GetPos().y,	// 원래 텍스처의 위치 새로 지정함
	//	SRCCOPY);
	
	//_background->Render(hdc);
	_actor->Render(hdc);
}
