#pragma once
#include "SpriteActor.h"

class Player;

class Item : SpriteActor
{
	using Super = SpriteActor;

public:
	Item();
	virtual ~Item() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	// 주인
	Player* _owner = nullptr;

	// 아이템 정보 - 이름, 설명, 사진(ResourceManager에서)

};

