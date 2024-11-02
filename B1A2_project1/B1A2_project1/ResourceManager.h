#pragma once

class ResourceBase;
class Texture;

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

private:
	HWND _hwnd;
	std::filesystem::path _resourcePath;

	// Resources
	std::unordered_map<std::wstring, Texture*> _textures;
};

