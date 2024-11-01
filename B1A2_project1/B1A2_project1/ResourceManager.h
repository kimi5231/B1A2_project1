#pragma once

class ResourceBase;

class ResourceManager
{
public:
	DECLARE_SINGLE(ResourceManager);

	~ResourceManager();

public:
	void Init(HWND hwnd, std::filesystem::path resourcePath);
	void Clear();

	const std::filesystem::path& GetResourcePath() { return _resourcePath; }

private:
	HWND _hwnd;
	std::filesystem::path _resourcePath;
};

