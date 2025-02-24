#pragma once
class ResourceBase;
class Texture;
class Sprite;
class Flipbook;
class Sound;
class Tilemap;
class Dialogue;
class LineInfo;
class Item;
struct PlayerStat;
struct TiredOfficeWorkerStat;
struct AmateurFencerStat;

struct SaveData
{
	int32 monsterCnt;
	// 몬스터 체력 - 동적할당 하기!!
	int32 playerHp;
	int32 skillPoint;
	std::unordered_map<int32, int32> acquiredItems;	// // [아이템 ID, 개수]
};

class ResourceManager
{
public:
	DECLARE_SINGLE(ResourceManager);

	~ResourceManager();

public:
	void Init(HWND hwnd, std::filesystem::path resourcePath);
	void Clear();

	const std::filesystem::path& GetResourcePath() { return _resourcePath; }

	Texture* GetTexture(const std::wstring& key) { return _textures[key]; }
	Texture* LoadTexture(const std::wstring& key, const std::wstring& path, uint32 transparent = RGB(255, 0, 255));

	Sprite* GetSprite(const std::wstring& key) { return _sprites[key]; }
	Sprite* CreateSprite(const std::wstring& key, Texture* texture, int32 x = 0, int32 y = 0, int32 cx = 0, int32 cy = 0);

	Flipbook* GetFlipbook(const std::wstring& key) { return _flipbooks[key]; }
	Flipbook* CreateFlipbook(const std::wstring& key);

	Sound* GetSound(const std::wstring& key) { return _sounds[key]; }
	Sound* LoadSound(const std::wstring& key, const std::wstring& path);

	Tilemap* GetTilemap(const std::wstring& key) { return _tilemaps[key]; }
	Tilemap* CreateTilemap(const std::wstring& key);
	Tilemap* LoadTilemap(const std::wstring& key, const std::wstring& path);
	void SaveTilemap(const std::wstring& key, const std::wstring& path);

	Dialogue* GetDialogue(const std::wstring& key) { return _dialogues[key]; }
	Dialogue* LoadDialogue(const std::wstring& key, const std::wstring& path);

	Item* GetItem(const std::wstring& key) { return _items[key]; }
	Item* LoadItem(const std::wstring& key, const std::wstring& path);

	PlayerStat* GetPlayerStat() { return _playerStat; }
	PlayerStat* LoadPlayerStat(const std::wstring& path);

	TiredOfficeWorkerStat* GetTiredOfficeWorkerStat() { return _tiredOfficeWorkerStat; }
	TiredOfficeWorkerStat* LoadTiredOfficeWorkerStat(const std::wstring& path);

	AmateurFencerStat* GetAmateurFencerStat() { return _amateurFencerStat; }
	AmateurFencerStat* LoadAmateurFencerStat(const std::wstring& path);

	void SaveCurData();
private:
	HWND _hwnd;
	std::filesystem::path _resourcePath;

	// Resources
	std::unordered_map<std::wstring, Texture*> _textures;
	std::unordered_map<std::wstring, Sprite*> _sprites;
	std::unordered_map<std::wstring, Flipbook*> _flipbooks;
	std::unordered_map<std::wstring, Sound*> _sounds;
	std::unordered_map<std::wstring, Tilemap*> _tilemaps;
	std::unordered_map<std::wstring, Dialogue*> _dialogues;
	std::unordered_map<std::wstring, Item*> _items;
	PlayerStat* _playerStat;
	TiredOfficeWorkerStat* _tiredOfficeWorkerStat;
	AmateurFencerStat* _amateurFencerStat;
};

