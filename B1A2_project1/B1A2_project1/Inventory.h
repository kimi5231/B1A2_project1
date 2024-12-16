#pragma once
#include "Component.h"

class Item;
class Flipbook;

class Inventory : public Component
{
	using Super = Component;

public:
	Inventory();
	virtual ~Inventory() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

public:
	InventoryState GetInventoryState() { return _inventoryState; }
	void SetInventoryState(InventoryState state) { _inventoryState = state; }

	void SavePlayerOwnItems();	// _items에 저장
	
private:
	// Inventory 창 
	InventoryState _inventoryState = InventoryState::Hidden;

	// Item Flipbook
	Flipbook* _flipbookKey[2] = {};		// [기본, 효과]
	Flipbook* _flipbookPencil[2] = {};
	Flipbook* _flipbookMatch[2] = {};

	std::vector<std::wstring> _items;	// Player가 가지고 있는 아이템의 정보 저장
};

