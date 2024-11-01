#include "pch.h"
#include "Button.h"

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

}

void Button::Render(HDC hdc)
{
	Super::Render(hdc);

}

void Button::SetButtonState(ButtonState state)
{
	_state = state;
}
