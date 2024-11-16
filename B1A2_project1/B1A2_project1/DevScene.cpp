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
#include "SoundManager.h"
#include "Sound.h"
#include "Tilemap.h"
#include "TilemapActor.h"

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
		_actors.push_back(player);
	}

	// Sound
	/*GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\BGM.wav");
	{
		Sound* sound = GET_SINGLE(ResourceManager)->GetSound(L"BGM");
		sound->Play(true);
	}*/

	// Tilemap
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp");
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Tile");
		
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", texture, 0, 0, 48, 48);
		
		Tilemap* tm = new Tilemap();
		tm->SetMapSize({ 63, 43 });
		tm->SetTileSize(48);

		TilemapActor* actor = new TilemapActor();
		actor->SetPos({0, 0});
		actor->SetShowDebug(true);
		actor->SetTilemap(tm);

		_actors.push_back(actor);
	}

	Super::Init();
}

void DevScene::Update()
{
	Super::Update(); 

	for(Actor* actor : _actors)
		actor->Tick();
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);

	for (Actor* actor : _actors)
		actor->Render(hdc);
}