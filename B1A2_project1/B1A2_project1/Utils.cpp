#include "pch.h"
#include "Utils.h"

void Utils::DrawRect(HDC hdc, Vec2 pos, Vec2Int size)
{
	::Rectangle(hdc, static_cast<int32>(pos.x - size.x / 2), static_cast<int32>(pos.y - size.y / 2), static_cast<int32>(pos.x + size.x / 2), static_cast<int32>(pos.y + size.y / 2));
}