#pragma once
#include "ResourceBase.h"

struct ItemInfo
{
	//int32 ID;
	std::wstring ID;	// ID의 문자열 버전
	std::wstring name;
	std::wstring explain;
};

class Item : public ResourceBase
{
public:
	Item();
	virtual ~Item() override;

public:
	virtual void LoadFile(const std::wstring& path) override;

private:
	std::unordered_map<std::wstring, ItemInfo*> _items;	
};

