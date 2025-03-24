#pragma once
#include "Projectile.h"

class SlashWave : public Projectile
{
	using Super = Projectile;
public:
	SlashWave();
	virtual ~SlashWave() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickMove();
	virtual void UpdateAnimation();

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

private:
	Flipbook* _flipbookMove[2];
};

