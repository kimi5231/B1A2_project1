#include "pch.h"
#include "Panel.h"

Panel::Panel()
{
}

Panel::~Panel()
{
}

void Panel::BeginPlay()
{
}

void Panel::Tick()
{
}

void Panel::Render(HDC hdc)
{
}

void Panel::AddChild(UI* ui)
{
	if (ui == nullptr)
		return;

	_children.push_back(ui);
}

bool Panel::RemoveChild(UI* ui)
{
	auto findIt = std::find(_children.begin(), _children.end(), ui);

	if (findIt == _children.end())
		return false;

	_children.erase(findIt);
	return true;
}