#include "pch.h"
#include "Utils.h"

void Utils::DrawRect(HDC hdc, Vec2 pos, Vec2Int size)
{
	::Rectangle(hdc, static_cast<int32>(pos.x - size.x / 2), static_cast<int32>(pos.y - size.y / 2), static_cast<int32>(pos.x + size.x / 2), static_cast<int32>(pos.y + size.y / 2));
}

void Utils::DrawRect(HDC hdc, Vec2 pos, int32 w, int32 h)
{
	::Rectangle(hdc, static_cast<int32>(pos.x - w / 2), static_cast<int32>(pos.y - h / 2), static_cast<int32>(pos.x + w / 2), static_cast<int32>(pos.y + h / 2));
}

void Utils::DrawCircle(HDC hdc, Vec2 pos, int32 radius)
{
	::Ellipse(hdc, static_cast<int32>(pos.x - radius), static_cast<int32>(pos.y - radius), static_cast<int32>(pos.x + radius), static_cast<int32>(pos.y + radius));
}

void Utils::DrawString(HDC hdc, const std::wstring& str, RECT rect)
{
	::DrawText(hdc, str.c_str(), -1, &rect, DT_LEFT);
}