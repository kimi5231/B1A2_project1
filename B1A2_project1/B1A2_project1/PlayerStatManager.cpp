#include "pch.h"
#include "PlayerStatManager.h"
#include <fstream>

PlayerStatManager::~PlayerStatManager()
{
	Clear();
}

void PlayerStatManager::Init(HWND hwnd, std::filesystem::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;
}

void PlayerStatManager::Clear()
{

}

PlayerStat* PlayerStatManager::LoadPlayerStats(const int32 playerID, const std::wstring& path)
{	
	std::filesystem::path fullpath = _resourcePath / path;

	std::ifstream playerDBFile(fullpath);
	if (!playerDBFile.is_open())
		return _playerStats[playerID];

	std::string line;
	int currentID = 0; // 현재 읽고 있는 플레이어 ID

	while (std::getline(playerDBFile, line))
	{
		if (line.empty())
			continue;

		std::istringstream lineStream(line);
		std::string cell;
		PlayerStat* stat = new PlayerStat();
		int column = 0;

		while (std::getline(lineStream, cell, '\t'))
		{
			++stat->playerID;
			switch (column)
			{
			// stoi : 문자열을 정수로 변환
			case 0: stat->healthPoint = std::stoi(cell); break;
			case 1: stat->runSpeed = std::stoi(cell); break;
			case 2: stat->crouchSpeed = std::stoi(cell); break;
			case 3: stat->jumpHeight = std::stoi(cell); break;
			case 4: stat->attRange = std::stoi(cell); break;
			case 5: stat->enemyExistInAttRange = (cell == "1"); break;
			case 6: stat->attID = std::stoi(cell); break;
			case 7: stat->attDamage = std::stoi(cell); break;
			case 8: stat->attStepDistance = std::stoi(cell); break;
			case 9: stat->skillPoint = std::stoi(cell); break;
			case 10: stat->skillDamage = std::stoi(cell); break;
			case 11: stat->skillRange = std::stoi(cell); break;
			case 12: stat->skillDuration = std::stoi(cell); break;
			case 13: stat->skillStepDistance = std::stoi(cell); break;
			}
			++column;
		}
		_playerStats[playerID] = stat;
		return stat;
	}
}
