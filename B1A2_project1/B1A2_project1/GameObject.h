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
	virtual void TickSkill() {};
	virtual void UpdateAnimation() {};

public:
	void SetState(ObjectState state);
	void SetDir(Dir dir);

protected:
	Vec2 _speed = {};
	Dir _dir = DIR_LEFT;
	ObjectState _state = ObjectState::Idle;
};