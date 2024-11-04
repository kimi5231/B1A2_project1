#pragma once
#include "UI.h"

enum ButtonState
{
	BS_Default,
	BS_Hovered,
	BS_Pressed,
	BS_Clicked,

	BS_MaxCount
};

class Button : public UI
{
	using Super = UI;
public:
	Button();
	virtual ~Button() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	RECT GetRect();
	bool IsMouseInRect();

	void SetButtonState(ButtonState state);

private:
	ButtonState _state = BS_Default;
};