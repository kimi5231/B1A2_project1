#pragma once
#include "Structure.h"

class LockedDoorAndKey : public Structure
{
	using Super = Structure;
public:
	LockedDoorAndKey();
	virtual ~LockedDoorAndKey() override;

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
	virtual void TickOff() {};
	virtual void UpdateAnimation();

public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetDoorPos(Vec2Int pos) { _doorPos = pos; }
	Vec2Int GetDoorPos() { return _doorPos; }
	void SetItemPos(Vec2Int pos) { _itemPos = pos; }
	Vec2Int GetItemPos() { return _itemPos; }

private:
	Flipbook* _flipbookLockedDoor = nullptr;
	Flipbook* _flipbookUnlockedDoor = nullptr;
	Flipbook* _flipbookKey = nullptr;

	bool _isKeyRender = false;

	Vec2Int _doorPos;
	Vec2Int _itemPos;

public:
	bool _isKeyAcquired = false;
};

