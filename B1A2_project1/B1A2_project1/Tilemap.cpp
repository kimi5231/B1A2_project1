#include "pch.h"
#include "Tilemap.h"
#include <fstream>
#include <iostream>

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}

void Tilemap::LoadFile(const std::wstring& path)
{
	std::wifstream ifs;

	ifs.open(path);

	// �ʿ� ���� Ÿ�� �� ��������
	ifs >> _mapSize.x >> _mapSize.y;

	SetMapSize(_mapSize);

	for (int32 y = 0; y < _mapSize.y; ++y)
	{
		std::wstring line;
		ifs >> line;

		for (int32 x = 0; x < _mapSize.x; ++x)
		{
			// line[x]�� �����̹Ƿ�, ���������� �ٲٱ� ���� ���� 0�� ��.
			_tiles[y][x].value = line[x] - L'0';
		}
	}

	ifs.close();
}

void Tilemap::SaveFile(const std::wstring& path)
{
	std::wofstream ofs;

	ofs.open(path);

	// �ʿ� ���� Ÿ�� �� ����
	ofs << _mapSize.x << std::endl;
	ofs << _mapSize.y << std::endl;

	// Ÿ�� �� ����
	for (int32 y = 0; y < _mapSize.y; ++y)
	{
		for (int32 x = 0; x < _mapSize.x; ++x)
		{
			ofs << _tiles[y][x].value;
		}
		ofs << std::endl;
	}

	ofs.close();
}

// Ư�� ��ǥ�� Ÿ���� ���� ���
Tile* Tilemap::GetTileAt(Vec2Int pos)
{
	if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y > _mapSize.y)
		return nullptr;

	return &_tiles[pos.y][pos.x];
}

void Tilemap::SetMapSize(Vec2Int size)
{
	_mapSize = size;

	_tiles = std::vector(size.y, std::vector<Tile>(size.x));

	for (int32 y = 0; y < size.y; y++)
	{
		for (int32 x = 0; x < size.x; x++)
			_tiles[y][x] = Tile{ 0 };
	}
}

//void Tilemap::SetTileSize(int32 size)
//{
//	_tileSize = size;
//}