#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"

#include <iostream>

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init(HWND hwnd, std::filesystem::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;
}

void ResourceManager::Clear()
{
	for (auto& item : _textures)
		SAFE_DELETE(item.second);

	_textures.clear();
}

Texture* ResourceManager::LoadTexture(const std::wstring& key, const std::wstring& path, uint32 transparent)
{
	if (_textures.find(key) != _textures.end())
		return _textures[key];

	std::filesystem::path fullpath = _resourcePath / path;		// /는 경로 결합 연산자
	std::wcout << "Current Path: " << std::filesystem::current_path() << std::endl;
	std::wcout << "Full Path: " << fullpath << std::endl;


	Texture* texture = new Texture();
	texture->LoadBMP(_hwnd, fullpath.c_str());
	texture->SetTransparent(transparent);
	_textures[key] = texture;

	return texture;
}
