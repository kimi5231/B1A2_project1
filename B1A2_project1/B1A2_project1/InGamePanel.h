#pragma once
#include "Panel.h"

class InGamePanel : public Panel
{
	using Super = UI;
public:
	InGamePanel();
	virtual ~InGamePanel() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
};

