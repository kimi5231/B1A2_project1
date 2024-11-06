#include "pch.h"
#include "StaticUI.h"

StaticUI::StaticUI()
{
}

StaticUI::~StaticUI()
{
}

void StaticUI::BeginPlay()
{
	Super::BeginPlay();
}

void StaticUI::Tick()
{
	Super::Tick();
}

void StaticUI::Render(HDC hdc)
{
	Super::Render(hdc);

	Utils::DrawRect(hdc, _pos, _size);
}