#pragma once
#include "GameObject.h"

class Creature : public GameObject
{
	using Super = GameObject;
public:
	Creature();
	virtual ~Creature() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() override {};
	virtual void TickMove() override {};
	virtual void TickDuckDown() override {};
	virtual void TickDuckDownMove() override {};
	virtual void TickJump() override {};
	virtual void TickNormalAttack() override {};
	virtual void TickSkill() override {};
	virtual void TickHang() override {};
	virtual void TickRelease() override {};
	virtual void TickHit() override {};
	virtual void TickDead() override {};
	virtual void TickChase() override {};
	virtual void TickRoaming() override {};
	virtual void UpdateAnimation() override {};

public:
	void SetStat(CommonStat stat) { _stat = stat; }
	CommonStat& GetStat() { return _stat; }

public:
	virtual void OnDameged(int32 damage);
	
protected:
	CommonStat _stat;
};

