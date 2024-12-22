#pragma once
#include "Component.h"

class Item;
class Flipbook;
class Player;

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

	Player* GetOwner() { return _owner; }
	void SetOwner(Player* owner) { _owner = owner; }

	// _items에 Player가 획득한 아이템 저장
	void SaveAcquireItems();
	
private:
	Player* _owner = {};

	// Inventory 창 
	InventoryState _inventoryState = InventoryState::Hidden;

	// Item Flipbook (효과는 아직..)
	Flipbook* _flipbookKey = {};	
	Flipbook* _flipbookPencil = {};
	Flipbook* _flipbookMatch = {};

	std::unordered_map<int32, int32> _acquiredItems;
};

