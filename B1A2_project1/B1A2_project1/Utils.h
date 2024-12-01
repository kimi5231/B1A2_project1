#pragma once
class Utils
{
public:
	static void DrawRect(HDC hdc, Vec2 pos, Vec2Int size);
	static void DrawRect(HDC hdc, Vec2 pos, int32 w, int32 h);

	static void DrawCircle(HDC hdc, Vec2 pos, int32 radius);

	static void DrawString(HDC hdc, Vec2 pos, std::wstring str);
};