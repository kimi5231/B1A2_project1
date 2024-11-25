#pragma once
#include "Player.h"		// PlayerStat struct 필요해서 전방선언 말고 include함 

class PlayerStatManager
{
public:
	DECLARE_SINGLE(PlayerStatManager);

	~PlayerStatManager();

public:
	void Init(HWND hwnd, std::filesystem::path resourcePath);
	void Clear();

	const std::filesystem::path& GetResourcePath() { return _resourcePath; }

	PlayerStat* GetPlayerStat(const int32 playerID) { return _playerStats[playerID]; }		// 싱글 플레이어 기본 아이디 1(지금은 1이고, 플레이어가 더 생기면 바꾸는 코드 추가 필요)
	PlayerStat* LoadPlayerStats(const int32 playerID, const std::wstring& path);

private:
	HWND _hwnd;
	std::filesystem::path _resourcePath;

	// PlayerStat
	std::unordered_map<int32, PlayerStat*> _playerStats;		// [PlayerID, PlayerStat]
};

