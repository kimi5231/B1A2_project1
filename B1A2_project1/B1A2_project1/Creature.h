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
	virtual void TickCloseAttack() override {};
	virtual void TickLongAttack() override {};
	virtual void TickSkill() override {};
	virtual void TickHang() override {};
	virtual void TickRelease() override {};
	virtual void TickHit() override {};
	virtual void TickDead() override {};
	virtual void TickChase() override {};
	virtual void TickRoaming() override {};
	virtual void TickReturn() override {};
	virtual void UpdateAnimation() override {};

public:
	void SetCommonStat(CommonStat stat) { _commonStat = stat; }
	CommonStat& GetCommonStat() { return _commonStat; }

	virtual int32 GetAttack() = 0;
	virtual int32& GetHp() = 0;

protected:
	virtual void OnDamaged(Creature* other);
	
protected:
	CommonStat _commonStat;
};

