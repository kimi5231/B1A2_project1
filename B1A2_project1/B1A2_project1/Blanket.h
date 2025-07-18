#pragma once
#include "Projectile.h"

class BoxCollider;

class Blanket : public Projectile
{
	using Super = Projectile;
public:
	Blanket();
	virtual ~Blanket() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickMove() override;
	virtual void UpdateAnimation() override;

public:
	virtual float GetSpeed() override;

	void SetDuartion(float duration) { _duration = duration; }
private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetDir(Dir dir) { _dir = dir; }

private:
	Flipbook* _flipbookBlanket;

	float _sumTime = 0.f;

	BoxCollider* _collider;

	float _spawnInterval;
	float _duration;
};

 