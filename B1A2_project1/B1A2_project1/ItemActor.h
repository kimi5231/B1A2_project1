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

protected:
	Player* _owner = nullptr;

private:
	// Item ¸®¼Ò½º
	//Sprite* _spriteItemInInven = {};
	//Sprite* _spriteItemInInvenEffect = {};
};

