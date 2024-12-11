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
	{
		// Script
		GET_SINGLE(ResourceManager)->LoadDialogue(L"Dialogue", L"Script\\Dialogues.csv");
		Dialogue* dialogue = GET_SINGLE(ResourceManager)->GetDialogue(L"Dialogue");
		GET_SINGLE(DialogueManager)->SetDialogue(dialogue);

		// Texture
		GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueCorner", L"Sprite\\Dialogue\\DialogueCorner.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueTail", L"Sprite\\Dialogue\\DialogueTail.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueWidth", L"Sprite\\Dialogue\\DialogueWidth.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueHeight", L"Sprite\\Dialogue\\DialogueHeight.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueBackground", L"Sprite\\Dialogue\\DialogueBackground.bmp");

		// Sprite
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"DialogueCorner");
		GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueCornerLeftTop", texture, 0, 0, 7, 6);
		GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueCornerRightTop", texture, 7, 0, 7, 6);
		GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueCornerLeftBottom", texture, 14, 0, 7, 6);
		GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueCornerRightBottom", texture, 21, 0, 7, 6);

		texture = GET_SINGLE(ResourceManager)->GetTexture(L"DialogueWidth");
		GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueWidthTop", texture, 0, 0, 1, 6);
		GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueWidthBottom", texture, 1, 0, 1, 6);

		texture = GET_SINGLE(ResourceManager)->GetTexture(L"DialogueHeight");
		GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueHeightLeft", texture, 0, 0, 7, 1);
		GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueHeightRight", texture, 7, 0, 7, 1);
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
		player->SetPos({ 400, 200 });
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

	// Tile Collision
	{
		// ground
		{
			Actor* ground1 = new Actor();
			ground1->SetPos({ 320, 440 });
			ground1->SetLayer(LAYER_TILEMAP);

			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 640, 80 });
				collider->SetCollisionLayer(CLT_GROUND);
				GET_SINGLE(CollisionManager)->AddCollider(collider);
				ground1->AddComponent(collider);
			}
			AddActor(ground1);
		}
		{
			Actor* ground2 = new Actor();
			ground2->SetPos({ 960, 840 });
			ground2->SetLayer(LAYER_TILEMAP);

			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 1920, 80 });
				collider->SetCollisionLayer(CLT_GROUND);
				GET_SINGLE(CollisionManager)->AddCollider(collider);
				ground2->AddComponent(collider);
			}
			AddActor(ground2);
		}
		{
			Actor* ground3 = new Actor();
			ground3->SetPos({ 1940, 440 });
			ground3->SetLayer(LAYER_TILEMAP);

			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 920, 80 });
				collider->SetCollisionLayer(CLT_GROUND);
				GET_SINGLE(CollisionManager)->AddCollider(collider);
				ground3->AddComponent(collider);
			}
			AddActor(ground3);
		}
		{
			Actor* ground4 = new Actor();
			ground4->SetPos({ 1200, 760 });
			ground4->SetLayer(LAYER_TILEMAP);

			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 80, 80 });
				collider->SetCollisionLayer(CLT_GROUND);
				GET_SINGLE(CollisionManager)->AddCollider(collider);
				ground4->AddComponent(collider);
			}
			AddActor(ground4);
		}
		{
			Actor* ground5 = new Actor();
			ground5->SetPos({ 1280, 680 });
			ground5->SetLayer(LAYER_TILEMAP);

			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 80, 80 });
				collider->SetCollisionLayer(CLT_GROUND);
				GET_SINGLE(CollisionManager)->AddCollider(collider);
				ground5->AddComponent(collider);
			}
			AddActor(ground5);
		}
		{
			Actor* ground6 = new Actor();
			ground6->SetPos({ 1360, 600 });
			ground6->SetLayer(LAYER_TILEMAP);

			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 80, 80 });
				collider->SetCollisionLayer(CLT_GROUND);
				GET_SINGLE(CollisionManager)->AddCollider(collider);
				ground6->AddComponent(collider);
			}
			AddActor(ground6);
		}
		{
			Actor* ground7 = new Actor();
			ground7->SetPos({ 1440, 520 });
			ground7->SetLayer(LAYER_TILEMAP);

			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 80, 80 });
				collider->SetCollisionLayer(CLT_GROUND);
				GET_SINGLE(CollisionManager)->AddCollider(collider);
				ground7->AddComponent(collider);
			}
			AddActor(ground7);
		}

		// top
		{
			Actor* top1 = new Actor();
			top1->SetPos({ 1200, 40 });
			top1->SetLayer(LAYER_TILEMAP);

			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 2400, 80 });
				collider->SetCollisionLayer(CLT_GROUND);
				GET_SINGLE(CollisionManager)->AddCollider(collider);
				top1->AddComponent(collider);
			}
			AddActor(top1);
		}

		{
			Actor* top2 = new Actor();
			top2->SetPos({ 4600, 40 });
			top2->SetLayer(LAYER_TILEMAP);

			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 2400, 80 });
				collider->SetCollisionLayer(CLT_GROUND);
				GET_SINGLE(CollisionManager)->AddCollider(collider);
				top2->AddComponent(collider);
			}
			AddActor(top2);
		}

		// wall
		{
			Actor* wall1 = new Actor();
			wall1->SetPos({ 40, 640 });
			wall1->SetLayer(LAYER_TILEMAP);
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ 80, 320 });
				collider->SetCollisionLayer(CLT_WALL);
				GET_SINGLE(CollisionManager)->AddCollider(collider);
				wall1->AddComponent(collider);
			}
			AddActor(wall1);
		}
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