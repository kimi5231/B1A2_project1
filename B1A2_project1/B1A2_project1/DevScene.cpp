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
#include "Scene.h"
#include "Player.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "DialogueManager.h"
#include "SceneManager.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	// 마지 리소스
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerMoveRight", L"Sprite\\Player\\PlayerMoveRight.bmp", RGB(55, 255, 0));	// 녹색 배경 (55, 255, 0)
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerMoveLeft", L"Sprite\\Player\\PlayerMoveLeft.bmp", RGB(55, 255, 0));	

	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerMoveRight");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerMoveRight");
		fb->SetInfo({ texture, L"FB_PlayerMoveRight", {67, 70}, 0, 9, 0, 0.7f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerMoveLeft");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerMoveLeft");
		fb->SetInfo({ texture, L"FB_PlayerMoveLeft", {67, 70}, 0, 9, 0, 0.7f });
	}

	// Dialogue
	GET_SINGLE(ResourceManager)->LoadDialogue(L"Dialogue", L"Script\\Dialogues.csv");
	Dialogue* dialogue = GET_SINGLE(ResourceManager)->GetDialogue(L"Dialogue");
	GET_SINGLE(DialogueManager)->SetDialogue(dialogue);

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

		AddActor(map);
	}

	// Tilemap
	//{
	//	// Tile Texture Load
	//	GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(128, 128, 128));
	//	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Tile");
	//	
	//	GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", texture, 0, 0, 48, 48);
	//	GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", texture, 48, 0, 48, 48);

	//	// Tilemap Load
	//	GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap", L"Tilemap\\Tilemap.txt");
	//	Tilemap* tm = GET_SINGLE(ResourceManager)->GetTilemap(L"Tilemap");
	//	//tm->SetTileSize(48);

	//	TilemapActor* actor = new TilemapActor();
	//	actor->SetPos({0, 0});
	//	actor->SetShowDebug(true);
	//	actor->SetTilemap(tm);
	//	actor->SetLayer(LAYER_TILEMAP);

	//	AddActor(actor);
	//}

	// Player
	{
		Player* player = new Player();
		player->SetPos({ 300, 300 });
		player->SetLayer(LAYER_OBJECT);
		player->SetID(L"1");

		// Colider
		{
			BoxCollider* collider = new BoxCollider();
			// 리셋 안 하면 모두 충돌함
			collider->ResetCollisionFlag();	

			// 나 자신을 설정
			 collider->SetCollisionLayer(CLT_OBJECT);

			// 충돌하고 싶은 객체 설정
			collider->AddCollisionFlagLayer(CLT_GROUND);	
			collider->AddCollisionFlagLayer(CLT_WALL);
			collider->AddCollisionFlagLayer(CLT_OBJECT);

			collider->SetSize({ 67, 70 });
			
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			player->AddComponent(collider);
		}

		AddActor(player);
		
		// Start Dialogue
		{
			std::vector<Actor*> actors;
			actors.push_back(player);
			GET_SINGLE(DialogueManager)->StartDialogue(L"test1", actors);
		}
	}


	// Tilemap Collision
	{
		// Tilemap Load
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap", L"Tilemap\\Tilemap.txt");	// x : 160개, y : 36개 
		Tilemap* tm = GET_SINGLE(ResourceManager)->GetTilemap(L"Tilemap");

		TilemapActor* actor = new TilemapActor();
		actor->SetPos({ 0, 0 });
		actor->SetTilemap(tm);
		actor->SetLayer(LAYER_TILEMAP);

		{
			Vec2Int mapSize = tm->GetMapSize();

			std::vector<std::vector<Tile>>& tiles = tm->GetTiles();

			Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

			int32 startX = 0;
			int32 startY = 0;
			int32 endX = winSize.x / MAP_TILE_SIZEX;
			int32 endY = winSize.y / MAP_TILE_SIZEY;

			int count = 0;

			for (int32 y = startY; y <= endY; ++y)
			{
				for (int32 x = startX; x <= endX; ++x)
				{
					if (tiles[y][x].value == 1)
					{
						Actor* tile = new Actor();
						tile->SetPos({ (float)x * MAP_TILE_SIZEX, (float)y * MAP_TILE_SIZEY });
						tile->SetLayer(LAYER_TILEMAP);

						{
							BoxCollider* collider = new BoxCollider();
							collider->SetSize({ 24, 24 });
							collider->SetCollisionLayer(CLT_GROUND);
							GET_SINGLE(CollisionManager)->AddCollider(collider);
							tile->AddComponent(collider);
							count++;
						}
					}
				}
			}
		}

		AddActor(actor);
	}

	// 충돌 객체 - 참고
	{
		Actor* test = new Actor();
		test->SetPos({ 500, 400 });
		test->SetLayer(LAYER_OBJECT);

		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ 50, 500 });
			collider->SetCollisionLayer(CLT_OBJECT);
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			test->AddComponent(collider);
		}

		AddActor(test);
	}


	Super::Init();
}

void DevScene::Update()
{
	Super::Update(); 
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);
}