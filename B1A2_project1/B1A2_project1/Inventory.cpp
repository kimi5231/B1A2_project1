#include "pch.h"
#include "Inventory.h"
#include "ValueManager.h";
#include "ResourceManager.h"
#include "Texture.h"
#include "Player.h"
#include "Item.h"

Inventory::Inventory()
{
	// Flipbook
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

	// 인벤토리 판
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

	// _acquiredItems에서 정보 꺼내와서 출력(인벤토리 안, 숫자 / 마우스 대면 - 인벤토리 안 플립북 변경, 사진, 설명)
		
}

void Inventory::SaveAcquireItems()
{
	if (!_owner)
		return;

	// Player에 저장된 _acquiredItems 가져옴
	_acquiredItems = _owner->GetAquireItems();
}

