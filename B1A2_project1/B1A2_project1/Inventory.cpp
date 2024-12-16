#include "pch.h"
#include "Inventory.h"
#include "ValueManager.h";
#include "ResourceManager.h"
#include "Texture.h"

Inventory::Inventory()
{
	_flipbookKey = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_keyInInventory");
	_flipbookPencil = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_pencilInInventory");
	_flipbookMatch = GET_SINGLE(ResourceManager)->GetFlipbook(L"1003_matchInMap");
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

	// 가지고 있는 아이템 정보 가져오기
	
	// 설명

	// 사진

	// 인벤토리 안
}

void Inventory::GetPlayerOwnItems()
{
}

