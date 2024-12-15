#include "pch.h"
#include "ItemActor.h"
#include <fstream>
#include <iostream>
#include <string>
#include "ResourceManager.h"

ItemActor::ItemActor(ItemType itemType)
{
	if (itemType == ItemType::Key)
	{
		_sprite = GET_SINGLE(ResourceManager)->GetSprite(L"1001_key_inMap");
	}
	else if (itemType == ItemType::Pencil)
	{
		_sprite = GET_SINGLE(ResourceManager)->GetSprite(L"1002_pencil_inMap");	
	}
	else if (itemType == ItemType::Match)
	{
		_sprite = GET_SINGLE(ResourceManager)->GetSprite(L"1003_match_inMap");
	}
}

ItemActor::~ItemActor()
{
}

void ItemActor::BeginPlay()
{
	Super::BeginPlay();
}

void ItemActor::Tick()
{
	Super::Tick();
}

void ItemActor::Render(HDC hdc)
{
	Super::Render(hdc);
}
