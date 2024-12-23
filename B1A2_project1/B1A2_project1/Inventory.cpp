#include "pch.h"
#include "Inventory.h"
#include "ValueManager.h";
#include "ResourceManager.h"
#include "Texture.h"
#include "Player.h"
#include "Item.h"
#include "FlipbookActor.h"
#include "Flipbook.h"

Inventory::Inventory()
{
	// Flipbook
	_flipbookKey = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_keyInInventory");
	_flipbookPencil = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_pencilInInventory");
	_flipbookMatch = GET_SINGLE(ResourceManager)->GetFlipbook(L"1003_matchInInventory");

	// csv 파일로 저장한 Item 정보 가져옴
	_itemList = GET_SINGLE(ResourceManager)->GetItem(L"Item");
	_itemInfo = _itemList->GetItems();
}

Inventory::~Inventory()
{
}

void Inventory::BeginPlay()
{
}

void Inventory::TickComponent()
{
}

void Inventory::Render(HDC hdc)
{
	if (_inventoryState == InventoryState::Hidden)
		return;

	// 보정 변수 가져오기
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	Vec2 cameraPosAdjustmemt = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();

	// 인벤토리 판
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Inventory");
		::TransparentBlt(hdc,
			0,
			0,
			texture->GetSize().x,
			texture->GetSize().y,
			texture->GetDC(),
			0,
			0,
			texture->GetSize().x,
			texture->GetSize().y,
			texture->GetTransparent());
	}

	// _acquiredItems에서 정보 꺼내와서 출력(인벤토리 안, 숫자 / 마우스 대면 - 인벤토리 안 플립북 변경, 사진, 설명)
	if (_acquiredItems.empty())	// 획득한 아이템이 없으면 안 그림
		return;

	// Item
	{
		int32 i = 0;	// 위치 조정 Count
		for (auto it = _acquiredItems.begin(); it != _acquiredItems.end(); ++it, ++i)
		{
			int32 itemID = it->first;
			int32 itemCount = it->second;

			// 아이템의 정보 가져오기
			auto itemInfoIt = _itemInfo.find(itemID);
			if (itemInfoIt != _itemInfo.end())
				const ItemInfo* itemInfo = itemInfoIt->second;

			// 출력할 리소스 정하기
			Texture* texture = nullptr;

			switch (itemID)
			{
			case 1001:
				texture = GET_SINGLE(ResourceManager)->GetTexture(L"1001_keyInInventory"); break;
				break;
			case 1002:
				texture = GET_SINGLE(ResourceManager)->GetTexture(L"1002_pencilInInventory"); break;
			case 1003:
				texture = GET_SINGLE(ResourceManager)->GetTexture(L"1003_matchInInventory"); break;
			}

			::TransparentBlt(hdc,
				ITEM_STARTX + (i % 5) * ITEM_SIZEX,
				ITEM_STARTY + (i / 5) * ITEM_SIZEY,
				ITEM_SIZEX,
				ITEM_SIZEY,
				texture->GetDC(),
				0,
				0,
				ITEM_SIZEX,
				ITEM_SIZEY,
				texture->GetTransparent());
		}	
	}
	
}

void Inventory::SaveAcquireItems()
{
	if (!_owner)
		return;

	// Player에 저장된 _acquiredItems 가져옴
	_acquiredItems = _owner->GetAquireItems();
}

