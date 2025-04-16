#pragma once
#include "Structure.h"

class FootHold;

class FootHoldAndZipLineButton : public Structure
{
	using Super = Structure;
public:
	FootHoldAndZipLineButton();
	virtual ~FootHoldAndZipLineButton() override;

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
	virtual void TickThrust() {};
	virtual void TickBackStep() {};
	virtual void TickSlashWave() {};
	virtual void TickSkill() {};
	virtual void TickHang() {};
	virtual void TickRelease() {};
	virtual void TickHit() {};
	virtual void TickDead() {};
	virtual void TickChase() {};
	virtual void TickRoaming() {};
	virtual void TickDash() {};
	virtual void TickReturn() {};
	virtual void TickReturnIdle() {};

	virtual void TickOn() {};
	virtual void TickOn2();
	virtual void TickOff() {};
	virtual void UpdateAnimation();

public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	ObjectState GetState() { return _state; }

	void SetZipLinePos(Vec2 pos) { _zipLinePos = pos; }
	Vec2 GetZipLinePos() { return _zipLinePos; }

private:
	Flipbook* _flipbookFootHoldAndZipLineButtonOff = nullptr;
	Flipbook* _flipbookFootHoldAndZipLineButtonOn1 = nullptr;
	Flipbook* _flipbookFootHoldAndZipLineButtonOn2 = nullptr;

	Vec2 _zipLinePos = {};
};

/////////////////////////////////////////////////////////////////////////////////

class FootHold : public Structure
{
	using Super = Structure;
public:
	FootHold();
	virtual ~FootHold();
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
	virtual void TickThrust() {};
	virtual void TickBackStep() {};
	virtual void TickSlashWave() {};
	virtual void TickSkill() {};
	virtual void TickHang() {};
	virtual void TickRelease() {};
	virtual void TickHit() {};
	virtual void TickDead() {};
	virtual void TickChase() {};
	virtual void TickRoaming() {};
	virtual void TickDash() {};
	virtual void TickReturn() {};
	virtual void TickReturnIdle() {};
	virtual void UpdateAnimation();
	
	virtual void TickOff();
	virtual void TickOn() {};
	void TickReady();
public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetFootHoldAndZipLineButton(FootHoldAndZipLineButton* button) { _footHoldAndZipLineButton = button; }
	FootHoldAndZipLineButton* GetFootHoldAndZipLineButton() { return _footHoldAndZipLineButton; }

private:
	Flipbook* _flipbookFootHold = nullptr;

	ObjectState _state = ObjectState::Off;

	FootHoldAndZipLineButton* _footHoldAndZipLineButton = nullptr;
};

