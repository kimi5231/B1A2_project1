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

	void GetPlayerOwnItems();	// _items에 저장
	
private:
	// Inventory 창 
	InventoryState _inventoryState = InventoryState::Hidden;

	// Item Flipbook (효과는 아직..)
	Flipbook* _flipbookKey = {};	
	Flipbook* _flipbookPencil = {};
	Flipbook* _flipbookMatch = {};

	std::vector<std::wstring> _items;	// Player가 가지고 있는 아이템의 정보 저장
};

