#pragma once
#include "ItemActor.h"
#include "SpriteActor.h"

class Sprite;
class Player;
class Item;

class ItemActor : public SpriteActor
{
	using Super = SpriteActor;

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

protected:
	Player* _owner = nullptr;

private:
	// Item 리소스
	//Sprite* _spriteItemInInven = {};
	//Sprite* _spriteItemInInvenEffect = {};
};

