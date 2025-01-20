#pragma once
#include "UI.h"

class InGameUI : public UI
{
	using Super = UI;
public:
	InGameUI();
	virtual ~InGameUI() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
};

