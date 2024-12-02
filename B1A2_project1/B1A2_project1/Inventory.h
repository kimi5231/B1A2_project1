#pragma once
#include "Component.h"

class Item;

class Inventory : public Component
{
	using Super = Component;

public:
	Inventory();
	virtual ~Inventory() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;


};

