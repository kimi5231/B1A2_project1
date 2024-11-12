#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "Texture.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::BeginPlay()
{
	Super::BeginPlay();

	SetButtonState(BS_Default);
}

void Button::Tick()
{
	Super::Tick();

	if (IsMouseInRect())
	{
		SetButtonState(BS_Hovered);

		if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
		{
			_onClick();
		}
	}
	else
	{
		SetButtonState(BS_Default);
	}

	if (_currentFlipbook == nullptr)
		return;

	const FlipbookInfo& info = _currentFlipbook->GetInfo();
	if (info.loop == false && _idx == info.end)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	int32 frameCount = info.end - info.start + 1;
	float delta = info.duration / frameCount;

	if (_sumTime >= delta)
	{
		_sumTime = 0.f;
		_idx = (_idx + 1) % frameCount;
	}
}

void Button::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_currentFlipbook == nullptr)
	{
		Utils::DrawRect(hdc, _pos, _size);
	}
	else
	{
		const FlipbookInfo& info = _currentFlipbook->GetInfo();

		::TransparentBlt(hdc,
			(int32)_pos.x - info.size.x / 2,
			(int32)_pos.y - info.size.y / 2,
			info.size.x,
			info.size.y,
			info.texture->GetDC(),
			(info.start + _idx) * info.size.x,
			info.line * info.size.y,
			info.size.x,
			info.size.y,
			info.texture->GetTransparent());
	}
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
	if (_state == state)
		return;

	_state = state;

	SetCurrentFlipbook(state);
	Reset();
}

void Button::SetFlipbook(Flipbook* flipbook, ButtonState state)
{
	if (flipbook == nullptr)
		return;

	_flipbooks[state] = flipbook;

	Reset();
}

void Button::Reset()
{
	_idx = 0;
	_sumTime = 0.f;
}