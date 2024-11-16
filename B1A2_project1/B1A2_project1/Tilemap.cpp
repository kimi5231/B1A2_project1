#include "pch.h"
#include "Tilemap.h"

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}

void Tilemap::LoadFile(const std::wstring& path)
{
}

void Tilemap::SaveFile(const std::wstring& path)
{
}

// 특정 좌표의 타일의 정보 얻기
Tile* Tilemap::GetTileAt(Vec2Int pos)
{
	if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y > _mapSize.y)
		return nullptr;

	return &_tiles[pos.x][pos.y];
}

void Tilemap::SetMapSize(Vec2Int size)
{
	_mapSize = size;

	_tiles = std::vector(size.y, std::vector<Tile>(size.x));

	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
			_tiles[y][x] = Tile{ 0 };
	}
}

void Tilemap::SetTileSize(int32 size)
{
	_tileSize = size;
}
