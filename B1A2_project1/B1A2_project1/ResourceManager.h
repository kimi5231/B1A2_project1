#pragma once

class ResourceBase;
class Texture;
class Sprite;

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

private:
	HWND _hwnd;
	std::filesystem::path _resourcePath;

	// Resources
	std::unordered_map<std::wstring, Texture*> _textures;
	std::unordered_map<std::wstring, Sprite*> _sprites;
};

