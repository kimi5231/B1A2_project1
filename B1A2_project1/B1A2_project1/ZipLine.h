#pragma once
#include "Structure.h"

class ZipLine : public Structure
{
	using Super = Structure;
public:
	ZipLine();
	virtual ~ZipLine() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() {};
	virtual void TickMove() {};
	virtual void TickDuckDown() {};
	virtual void TickDuckDownMove() {};
	virtual void TickJump() {};
	virtual void TickCloseAttack() {};
	virtual void TickLongAttack() {};
	virtual void TickSkill() {};
	virtual void TickHang() {};
	virtual void TickRelease() {};
	virtual void TickHit() {};
	virtual void TickDead() {};
	virtual void TickChase() {};
	virtual void TickRoaming() {};
	virtual void TickReturn() {};
	virtual void TickReturnIdle() {};
	virtual void UpdateAnimation() {};

public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetZipLineType(ZipLineType type) { _zipLineType = type; }

private:
	Flipbook* _flipbookZipLine = nullptr;
	Flipbook* _flipbookZipLineGrip = nullptr;

	ZipLineType _zipLineType;
};

class ZipLineButton : public Structure
{
	using Super = Structure;
public:
	ZipLineButton();
	virtual ~ZipLineButton() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() {};
	virtual void TickMove() {};
	virtual void TickDuckDown() {};
	virtual void TickDuckDownMove() {};
	virtual void TickJump() {};
	virtual void TickCloseAttack() {};
	virtual void TickLongAttack() {};
	virtual void TickSkill() {};
	virtual void TickHang() {};
	virtual void TickRelease() {};
	virtual void TickHit() {};
	virtual void TickDead() {};
	virtual void TickChase() {};
	virtual void TickRoaming() {};
	virtual void TickReturn() {};
	virtual void TickReturnIdle() {};
	virtual void UpdateAnimation();

public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetOwner(ZipLine* zipLine) { _owner = zipLine; }

private:
	Flipbook* _flipbookButtonOff = nullptr;
	Flipbook* _flipbookButtonOn = nullptr;
	Flipbook* _flipbookDisplayOff = nullptr;
	Flipbook* _flipbookDisplayOn = nullptr;

private:
	ZipLine* _owner = nullptr;
};
