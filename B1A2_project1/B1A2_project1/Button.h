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

public:
	// CallBack 함수 연결을 위한 템플릿 함수
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]()
			{
				(owner->*func)();
			};
	}

	std::function<void(void)> _onClick = nullptr;
};