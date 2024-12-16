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
#include "ItemActor.h"

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
		GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueTriangle", L"Sprite\\Dialogue\\DialogueTriangle.bmp", RGB(55, 255, 0));

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

	// Item
	{
		// Item info
		GET_SINGLE(ResourceManager)->LoadItem(L"Item", L"DataBase\\itemList.csv");

		// Texture
		GET_SINGLE(ResourceManager)->LoadTexture(L"F_key", L"Sprite\\Item\\F_key.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"1001_keyInMap", L"Sprite\\Item\\1001_keyInMap.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"1002_pencilInMap", L"Sprite\\Item\\1002_pencilInMap.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"1003_matchInMap", L"Sprite\\Item\\1003_matchInMap.bmp", RGB(55, 255, 0));

		// Flipbook
		// F button
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"F_key");
			GET_SINGLE(ResourceManager)->CreateSprite(L"F_key", texture, 0, 0, 30, 30);
		}
		// 1001_Key
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"1001_keyInMap");
			
			// in Map
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_keyInMap");
				fb->SetInfo({ texture, L"FB_keyInMap", {30, 30}, 0, 2, 0, 0.7f, true });
			}

			// in Inventory
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_keyInInventory");
				fb->SetInfo({ texture, L"FB_keyInInventory", {128, 128}, 0, 2, 0, 0.7f, true });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_keyInInventoryEffect");
				fb->SetInfo({ texture, L"FB_keyInInventoryEffect", {128, 128}, 0, 2, 1, 0.7f, true });
			}

		}
		// 1002_pencil
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"1002_pencilInMap");
			
			// in Map
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_pencilInMap");
				fb->SetInfo({ texture, L"FB_pencilInMap", {30, 30}, 0, 2, 0, 0.7f, true });
			}

			// in Inventory
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_pencilInInventory");
				fb->SetInfo({ texture, L"FB_pencilInventory", {128, 128}, 0, 2, 0, 0.7f, true });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_pencilInInventoryEffect");
				fb->SetInfo({ texture, L"FB_pencilInventoryEffect", {128, 128}, 0, 2, 1, 0.7f, true });
			}
		}
		// 1003_match
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"1003_matchInMap");
			
			// in Map
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_matchInMap");
				fb->SetInfo({ texture, L"FB_matchInMap", {30, 30}, 0, 2, 0, 0.7f, true });
			}

			// in Inventory
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_matchInInventory");
				fb->SetInfo({ texture, L"FB_matchInInventory", {128, 128}, 0, 2, 0, 0.7f, true });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_matchInInventoryEffect");
				fb->SetInfo({ texture, L"FB_matchInInventoryEffect", {128, 128}, 0, 2, 1, 0.7f, true });
			}
		}		
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
	{
		// Tilemap Load
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap", L"Tilemap\\Tilemap.txt"); 
		Tilemap* tm = GET_SINGLE(ResourceManager)->GetTilemap(L"Tilemap");

		TilemapActor* actor = new TilemapActor();
		actor->SetPos({0, 0});
		actor->SetShowDebug(false);
		actor->SetTilemap(tm);
		actor->SetLayer(LAYER_TILEMAP);

		AddActor(actor);
	}

	// Player
	{
		Player* player = new Player();
		player->SetPos({ 400, 200 });
		player->SetLayer(LAYER_PLAYER);
		player->SetID(1);

		// Colider
		{
			BoxCollider* collider = new BoxCollider();
			// 리셋 안 하면 모두 충돌함
			collider->ResetCollisionFlag();	

			// 나 자신을 설정
			 collider->SetCollisionLayer(CLT_PLAYER);

			// 충돌하고 싶은 객체 설정
			collider->AddCollisionFlagLayer(CLT_GROUND);	
			collider->AddCollisionFlagLayer(CLT_WALL);

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

	// Item
	{
		ItemActor* item = new ItemActor(ItemType::Match);
		item->SetPos({ 100, 200 });		// 적당한 y 좌표 : 370
		item->SetLayer(LAYER_ITEM);
		item->SetID(1);	// ID 관련 상의 필요 - 읽을 때는 문자열로(key 구분), 생성 시 Scene에서 ID를 따로 설정하는 방식으로!?

		// Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ 100, 55 });	// 원래 크기보다 크게 설정
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_ITEM);
			collider->AddCollisionFlagLayer(CLT_PLAYER);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			item->AddComponent(collider);
		}
		AddActor(item);
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