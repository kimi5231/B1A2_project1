#pragma once

#include "FlipbookActor.h"

class Player : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	// 젤다 리소스
	Flipbook* _flipbookLeft = nullptr;
	Flipbook* _flipbookRight = nullptr;

	// 마지 리소스
	Flipbook* _flipbookPlayerRunRight = nullptr;
};

