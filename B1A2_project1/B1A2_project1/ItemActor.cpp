#include "pch.h"
#include "ItemActor.h"
#include <fstream>
#include <iostream>
#include <string>
#include "ResourceManager.h"

ItemActor::ItemActor(ItemType itemType)
{
	if (itemType == ItemType::Pencil)
	{
		_spriteItemInMap = GET_SINGLE(ResourceManager)->GetSprite(L"1002_pencil_inMap");
		_spriteItemInInven = GET_SINGLE(ResourceManager)->GetSprite(L"1002_pencil_inInven");
		_spriteItemInInvenEffect = GET_SINGLE(ResourceManager)->GetSprite(L"1002_pencil_inInvenEffect");
	}
}

ItemActor::~ItemActor()
{
}

void ItemActor::BeginPlay()
{
}

void ItemActor::Tick()
{
}

void ItemActor::Render(HDC hdc)
{

}
