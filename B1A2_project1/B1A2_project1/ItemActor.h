#pragma once
#include "ItemActor.h"
#include "SpriteActor.h"

class Player;
class Item;

class ItemActor : public SpriteActor
{
	using Super = SpriteActor;

public:
	ItemActor();
	virtual ~ItemActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	Player* _owner = nullptr;
};

