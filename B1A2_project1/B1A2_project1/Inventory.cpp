#include "pch.h"
#include "Inventory.h"
#include "ValueManager.h";
#include "ResourceManager.h"
#include "Texture.h"

Inventory::Inventory()
{

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

}

void Inventory::SavePlayerOwnItems()
{
}

