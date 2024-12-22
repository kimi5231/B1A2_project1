#pragma once
#include "ItemActor.h"
#include "FlipbookActor.h"

class Player;
class Item;

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
	// Collider - 아이템 범위 내로 들어오면 F키 나옴 (튕기기 X)
	virtual void OnConponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	int32 GetItemID() { return _itemID; }
	void SetItemID(int32 id) { _itemID = id; }

	Player* GetOwner() { return _owner; }
	void SetOwner(Player* player) { _owner = player; }

public:
	void SetFKeyState(FKeyState state) { _FkeyState = state; }
	FKeyState GetFKeyState() { return _FkeyState; }

protected:
	Player* _owner = nullptr;

private:
	int32 _itemID = {};

	Flipbook* _flipbookItemInMap = {};
	Flipbook* _flipbookFKey = {};

private:
	FKeyState _FkeyState = FKeyState::Hidden;
};

