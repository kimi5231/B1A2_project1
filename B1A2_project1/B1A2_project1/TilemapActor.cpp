#include "pch.h"
#include "TilemapActor.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Tilemap.h"
#include "Sprite.h"

TilemapActor::TilemapActor()
{
}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();
}

void TilemapActor::Tick()
{
	Super::Tick();
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (!_showDebug)
		return;

	if (_tilemap == nullptr)
		return;

	Vec2Int mapSize = _tilemap->GetMapSize();
	int32 tileSize = _tilemap->GetTileSize();

	std::vector<std::vector<Tile>>& tiles = _tilemap->GetTiles();

	Sprite* spriteO = GET_SINGLE(ResourceManager)->GetSprite(L"TileO");
	Sprite* spriteX = GET_SINGLE(ResourceManager)->GetSprite(L"TileX");

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	// 컬링
	// 카메라 좌표의 시작과 끝을 구하기
	int32 leftX = (int32)cameraPos.x - GWinSizeX / 2;
	int32 leftY = (int32)cameraPos.y - GWinSizeY / 2;
	int32 rightX = (int32)cameraPos.x + GWinSizeX / 2;
	int32 rightY = (int32)cameraPos.y + GWinSizeY / 2;

	// 카메라 좌표의 시작과 끝을 월드 좌표로 변환한 후 인덱스 구하기
	int32 startX = (leftX - _pos.x) / TILE_SIZEX;
	int32 startY = (leftY - _pos.x) / TILE_SIZEY;
	int32 endX = (rightX - _pos.x) / TILE_SIZEX;
	int32 endY = (rightY - _pos.y) / TILE_SIZEY;

	for (int y = startY; y <= endY; ++y)
	{
		for (int x = startX; x <= endX; ++x)
		{
			if (x < 0 || x >= mapSize.x)
				continue;
			if (y < 0 || y >= mapSize.y)
				continue;

			switch (tiles[y][x].value)
			{
			case 0:
				::TransparentBlt(hdc,
					_pos.x + x * TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2),
					_pos.y + y * TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2),
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetDC(),
					spriteO->GetPos().x,
					spriteO->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetTransparent());
				break;
			case 1:
				::TransparentBlt(hdc,
					_pos.x + x * TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2),
					_pos.y + y * TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2),
					TILE_SIZEX,
					TILE_SIZEY,
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
