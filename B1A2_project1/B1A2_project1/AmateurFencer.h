#pragma once
#include "Monster.h"

class AmateurFencer : public Monster
{
	using Super = Monster;
public:
	AmateurFencer();
	virtual ~AmateurFencer() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
};

