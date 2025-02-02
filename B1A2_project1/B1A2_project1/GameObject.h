#pragma once
#include "FlipbookActor.h"

class GameObject : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	GameObject();
	virtual ~GameObject() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() {};
	virtual void TickMove() {};
	virtual void TickDuckDown() {};
	virtual void TickDuckDownMove() {};
	virtual void TickJump() {};
	virtual void TickNormalAttack() {};
	virtual void TickSkill() {};
	virtual void TickHang() {};
	virtual void TickRelease() {};
	virtual void TickHit() {};
	virtual void TickDead() {};
	virtual void TickChase() {};
	virtual void TickRoaming() {};
	virtual void UpdateAnimation() {};

public:
	void SetState(ObjectState state);
	void SetDir(Dir dir);

protected:
	Vec2 _speed = {};
	Dir _dir = DIR_LEFT;
	ObjectState _state = ObjectState::Idle;
};