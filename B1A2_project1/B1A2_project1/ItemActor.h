#pragma once
#include "ItemActor.h"
#include "FlipbookActor.h"

class Player;
class Item;
class Collider;

class ItemActor : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	ItemActor(ItemType itemType);
	virtual ~ItemActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	int32 GetItemID() { return _itemID; }
	void SetItemID(int32 id) { _itemID = id; }

	Player* GetOwner() { return _owner; }
	void SetOwner(Player* player) { _owner = player; }

public:
	void SetFKeyState(FKeyState state) { _FkeyState = state; }
	FKeyState GetFKeyState() { return _FkeyState; }

	void SetItemState(ItemState state) { _itemState = state; }
	ItemState GetItemState() { return _itemState; }

	// 아이템 삭제 위해
	Collider* GetCollider() const;
protected:
	Player* _owner = nullptr;

private:
	int32 _itemID = {};

	Flipbook* _flipbookItemInMap = {};
	Flipbook* _flipbookFKey = {};

private:
	FKeyState _FkeyState = FKeyState::Hidden;
	ItemState _itemState = ItemState::Show;
};

