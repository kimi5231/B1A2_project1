#include "pch.h"
#include "TilemapActor.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ValueManager.h"
#include "CollisionManager.h"
#include "Tilemap.h"
#include "Sprite.h"
#include "BoxCollider.h"

TilemapActor::TilemapActor()
{

}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();

	Vec2Int mapSize = _tilemap->GetMapSize();

	std::vector<std::vector<Tile>>& tiles = _tilemap->GetTiles();

	for (int32 y = 0; y < mapSize.y; ++y)
	{
		for (int32 x = 0; x < mapSize.x; ++x)
		{
			if (tiles[y][x].value == 1)
			{
				BoxCollider* collider = new BoxCollider();
				collider->SetSize({ MAP_TILE_SIZEX, MAP_TILE_SIZEY });
				collider->SetPos({ (float)(x * MAP_TILE_SIZEX + MAP_TILE_SIZEX / 2),
					(float)(y * MAP_TILE_SIZEY + MAP_TILE_SIZEY / 2) });
				// flag reset
				collider->ResetCollisionFlag();
				collider->SetCollisionLayer(CLT_GROUND);
				// 충돌할 객체
				collider->AddCollisionFlagLayer(CLT_PLAYER);
				GET_SINGLE(CollisionManager)->AddCollider(collider);
				AddComponent(collider);
			}
		}
	}
}

void TilemapActor::Tick()
{
	Super::Tick();

	if (!_showDebug)
		return;

	TickPicking();
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (!_showDebug)
		return;

	if (!_tilemap)
		return;

	Vec2Int mapSize = _tilemap->GetMapSize();

	std::vector<std::vector<Tile>>& tiles = _tilemap->GetTiles();

	Sprite* spriteO = GET_SINGLE(ResourceManager)->GetSprite(L"TileO");
	Sprite* spriteX = GET_SINGLE(ResourceManager)->GetSprite(L"TileX");

	Vec2 cameraPosAdjustment = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();
	Vec2 winSizeAdjustment = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	// 컬링
	// 카메라 좌표의 시작과 끝을 구하기
	int32 leftX = (int32)cameraPos.x - winSize.x / 2;
	int32 leftY = (int32)cameraPos.y - winSize.y / 2;
	int32 rightX = (int32)cameraPos.x + winSize.x / 2;
	int32 rightY = (int32)cameraPos.y + winSize.y / 2;

	// 카메라 좌표의 시작과 끝을 월드 좌표로 변환한 후 카메라에 보이는 타일 인덱스 범위 구하기
	int32 startX = (leftX - _pos.x) / MAP_TILE_SIZEX;
	int32 startY = (leftY - _pos.y) / MAP_TILE_SIZEY;
	int32 endX = (rightX - _pos.x) / MAP_TILE_SIZEX;
	int32 endY = (rightY - _pos.y) / MAP_TILE_SIZEY;

	for (int32 y = startY; y <= endY; ++y)
	{
		for (int32 x = startX; x <= endX; ++x)
		{
			if (x < 0 || x >= mapSize.x)
				continue;
			if (y < 0 || y >= mapSize.y)
				continue;

			switch (tiles[y][x].value)
			{
			case 0:
				::TransparentBlt(hdc,
					(_pos.x + x * MAP_TILE_SIZEX) * winSizeAdjustment.x - cameraPosAdjustment.x,
					(_pos.y + y * MAP_TILE_SIZEY) * ((float)winSize.y / (float)DefaultWinSizeY) - ((int32)cameraPos.y - winSize.y / 2),
					MAP_TILE_SIZEX * ((float)winSize.x / (float)DefaultWinSizeX),
					MAP_TILE_SIZEY * ((float)winSize.y / (float)DefaultWinSizeY),
					spriteO->GetDC(),
					spriteO->GetPos().x,
					spriteO->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetTransparent());
				break;
			case 1:
				::TransparentBlt(hdc,
					(_pos.x + x * MAP_TILE_SIZEX) * ((float)winSize.x / (float)DefaultWinSizeX) - ((int32)cameraPos.x - winSize.x / 2),
					(_pos.y + y * MAP_TILE_SIZEY) * ((float)winSize.y / (float)DefaultWinSizeY) - ((int32)cameraPos.y - winSize.y / 2),
					MAP_TILE_SIZEX * ((float)winSize.x / (float)DefaultWinSizeX),
					MAP_TILE_SIZEY * ((float)winSize.y / (float)DefaultWinSizeY),
					spriteX->GetDC(),
					spriteX->GetPos().x,
					spriteX->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetTransparent());
				break;
			}
		}
	}
}

void TilemapActor::TickPicking()
{
	// 드래그 가능
	if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftMouse))
	{
		Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		
		Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

		// 카메라 좌표
		int32 screenX = (int32)cameraPos.x - winSize.x / 2;
		int32 screenY = (int32)cameraPos.y - winSize.y / 2;

		// 월드 좌표
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		// 월드 좌표를 카메라 좌표로 변환
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		// 인덱스로 변환
		int32 x = posX / MAP_TILE_SIZEX;
		int32 y = posY / MAP_TILE_SIZEY;

		Tile* tile = _tilemap->GetTileAt({x, y});

		if (tile)
			tile->value = TILE_X;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::RightMouse))
	{
		Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

		Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

		// 카메라 좌표
		int32 screenX = (int32)cameraPos.x - winSize.x / 2;
		int32 screenY = (int32)cameraPos.y - winSize.y / 2;

		// 월드 좌표
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		// 월드 좌표를 카메라 좌표로 변환
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		// 인덱스로 변환
		int32 x = posX / MAP_TILE_SIZEX;
		int32 y = posY / MAP_TILE_SIZEY;

		Tile* tile = _tilemap->GetTileAt({ x, y });

		if (tile)
			tile->value = TILE_O;
	}
}