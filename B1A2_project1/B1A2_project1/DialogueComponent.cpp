#include "pch.h"
#include "DialogueComponent.h"
#include "Dialogue.h"
#include "Actor.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include <fstream>
#include <iostream>
#include <string>

DialogueComponent::DialogueComponent()
{
}

DialogueComponent::~DialogueComponent()
{
}

void DialogueComponent::BeginPlay()
{
	_fontSize = 20;
}

void DialogueComponent::TickComponent()
{
}

void DialogueComponent::Render(HDC hdc)
{
	if (!_owner)
		return;
	
	// owner 사이즈 가져오기
	FlipbookActor* owner = dynamic_cast<FlipbookActor*>(_owner);
	Flipbook* flipbook = owner->GetFlipbook();
	const FlipbookInfo& info = flipbook->GetInfo();
	Vec2Int size = info.size;

	// 이벤트 가져오기
	std::vector<LineInfo>& event = _dialogue->GetEvent(L"test1");

	// 폰트 생성
	HFONT hfont = CreateFont(
		-_fontSize,
		0, 
		0, 
		0, 
		FW_NORMAL, 
		FALSE, 
		FALSE, 
		FALSE, 
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_SWISS, 
		L"둥근모꼴");

	// 폰트 선택
	HFONT oldFont = (HFONT)SelectObject(hdc, hfont);

	// 배경색 투명화
	SetBkMode(hdc, TRANSPARENT);

	// 텍스트 출력 범위 사이즈 얻어오기
	Vec2Int rectSize = GetDialogueRectSize(hdc, event.begin()->speech);

	// Dialogue 위치 지정
	Vec2 ownerPos = _owner->GetPos();
	Vec2 pos = { ownerPos.x - (float)rectSize.x / 2, ownerPos.y - (float)size.y / 2 - rectSize.y };
	RECT rect = { pos.x, pos.y, pos.x + rectSize.x, pos.y + rectSize.y };

	Utils::DrawString(hdc, event.begin()->speech, rect);

	::SelectObject(hdc, oldFont);
	::DeleteObject(hfont);
}

Vec2Int DialogueComponent::GetDialogueRectSize(HDC hdc, const std::wstring& str)
{
	// 문자열 스트림 생성
	std::wistringstream wiss(str);

	std::wstring text;
	std::vector<std::wstring> texts;

	// 개행문자를 기준으로 문자열 분리
	while (std::getline(wiss, text, L'\n'))
		texts.push_back(text);

	SIZE textSize;
	int32 max = 0;

	// 가장 길이가 긴 문자열 길이 저장하기
	for (const std::wstring& text : texts)
	{
		::GetTextExtentPoint32(hdc, text.c_str(), text.length(), &textSize);
		if (max < textSize.cx)
			max = textSize.cx;
	}

	return Vec2Int{ max, (int32)texts.size() * _fontSize };
}