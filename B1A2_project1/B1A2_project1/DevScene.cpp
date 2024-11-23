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
#include "ValueManager.h"

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

	// Sound
	/*GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\BGM.wav");
	{
		Sound* sound = GET_SINGLE(ResourceManager)->GetSound(L"BGM");
		sound->Play(true);
	}*/

	// Map
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"TestMap", L"Sprite\\Map\\TestMap.bmp");

		Vec2Int mapSize = GET_SINGLE(ValueManager)->GetMapSize();
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TestMap");
		GET_SINGLE(ResourceManager)->CreateSprite(L"TestMap", texture, 0, 0, mapSize.x, mapSize.y);

		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"TestMap");
		SpriteActor* map = new SpriteActor();
		const Vec2Int size = sprite->GetSize();
		map->SetPos(Vec2(size.x / 2, size.y / 2));
		map->SetSprite(sprite);
		map->SetLayer(LAYER_BACKGROUND);

		_actors.push_back(map);
	}

	// Tilemap
	{
		// Tile Texture Load
		GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Tile");
		
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", texture, 0, 0, 48, 48);
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", texture, 48, 0, 48, 48);

		// Tilemap Load
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap", L"Tilemap\\Tilemap.txt");
		Tilemap* tm = GET_SINGLE(ResourceManager)->GetTilemap(L"Tilemap");
		//tm->SetTileSize(48);

		TilemapActor* actor = new TilemapActor();
		actor->SetPos({0, 0});
		actor->SetShowDebug(true);
		actor->SetTilemap(tm);

		_actors.push_back(actor);
	}

	{
		Player* player = new Player();
		player->SetPos({ 100, 100 });
		_actors.push_back(player);
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