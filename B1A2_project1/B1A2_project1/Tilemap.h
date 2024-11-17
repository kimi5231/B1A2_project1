#pragma once
#include "ResourceBase.h"
#include <string>
#include <string>

struct Tile
{
	int32 value = 0;
};

enum TILE_SIZE
{
	TILE_WIDTH = 40,
	TILE_HIGHT = 40,
	TILE_SIZEX = 48,
	TILE_SIZEY = 48,
};

class Tilemap : public ResourceBase
{
public:
	Tilemap();
	virtual ~Tilemap() override;

public:
	virtual void LoadFile(const std::wstring& path) override;
	virtual void SaveFile(const std::wstring& path) override;

	Vec2Int GetMapSize() { return _mapSize; }
	int32 GetTileSize() { return _tileSize; }
	Tile* GetTileAt(Vec2Int pos);
	std::vector<std::vector<Tile>>& GetTiles() { return _tiles; }

	void SetMapSize(Vec2Int size);
	void SetTileSize(int32 size);

private:
	// 맵에 들어가는 타일 수
	Vec2Int _mapSize{};
	int32 _tileSize = 0;
	std::vector<std::vector<Tile>> _tiles;
};

