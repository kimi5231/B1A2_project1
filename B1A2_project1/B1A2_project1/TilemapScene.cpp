#include "pch.h"
#include "TilemapScene.h"
#include "ResourceManager.h"
#include "Tilemap.h"
#include "Sprite.h"
#include "TilemapActor.h"
#include "SpriteActor.h"
#include "CameraActor.h"

TilemapScene::TilemapScene()
{
}

TilemapScene::~TilemapScene()
{
}

void TilemapScene::Init()
{
	// Texture
	GET_SINGLE(ResourceManager)->LoadTexture(L"TestMap", L"Sprite\\Map\\TestMap.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));

	// Sprite
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TestMap");
		GET_SINGLE(ResourceManager)->CreateSprite(L"TestMap", texture, 0, 0, mapX, mapY);
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Tile");
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", texture, 0, 0, 48, 48);
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", texture, 48, 0, 48, 48);
	}
	
	// Tilemap
	GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap", L"Tilemap\\Tilemap.txt");
	
	// Map
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"TestMap");
		SpriteActor* map = new SpriteActor();
		const Vec2Int size = sprite->GetSize();
		map->SetPos(Vec2(size.x / 2, size.y / 2));
		map->SetSprite(sprite);
		map->SetLayer(LAYER_BACKGROUND);

		_actors.push_back(map);
	}

	// TilemapActor
	{
		Tilemap* tilemap = GET_SINGLE(ResourceManager)->GetTilemap(L"Tilemap");
		TilemapActor* actor = new TilemapActor();
		actor->SetPos({ 0, 0 });
		actor->SetShowDebug(false);
		actor->SetTilemap(tilemap);

		_actors.push_back(actor);
	}
	
	// CameraActor
	{
		CameraActor* actor = new CameraActor();
		actor->SetPos({ 0, 0 });

		_actors.push_back(actor);
	}
	
	Super::Init();
}

void TilemapScene::Update()
{
	Super::Update();

	for (Actor* actor : _actors)
		actor->Tick();
}

void TilemapScene::Render(HDC hdc)
{
	Super::Render(hdc);

	for (Actor* actor : _actors)
		actor->Render(hdc);
}