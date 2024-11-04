#include "pch.h"
#include "Button.h"
#include "InputManager.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::BeginPlay()
{
	Super::BeginPlay();
}

void Button::Tick()
{
	Super::Tick();

	if (IsMouseInRect())
	{
		int a = 3;
	}
}

void Button::Render(HDC hdc)
{
	Super::Render(hdc);

	Utils::DrawRect(hdc, _pos, _size);
}

RECT Button::GetRect()
{
	RECT rect = {
		_pos.x - _size.x,
		_pos.y - _size.y,
		_pos.x + _size.x,
		_pos.y + _size.y
	};

	return rect;
}

bool Button::IsMouseInRect()
{
	RECT rect = GetRect();
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

	return ::PtInRect(&rect, mousePos);
}

void Button::SetButtonState(ButtonState state)
{
	_state = state;
}