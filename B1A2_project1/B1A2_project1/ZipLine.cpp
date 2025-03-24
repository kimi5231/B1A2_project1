#include "pch.h"
#include "ZipLine.h"
#include "ResourceManager.h"

// 1. 짚라인 - 버튼이 있는 버전과 버튼 없이 짚라인만 있는 버전
// 2. 짚라인 버튼 - Player와 충돌 처리되면 상호작용 입력을 받아 짚라인 활성화
// 3. 짚라인 전광판 - 버튼 활성화되면 Render

ZipLine::ZipLine(ZipLineType zipLineType)
{
	_flipbookZipLine = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLine");

	if (zipLineType == ZipLineType::ZipLineWithButton)
	{
		_flipbookButton;
		_flipbookDisplay;
	}
}

ZipLine::~ZipLine()
{
}

void ZipLine::BeginPlay()
{
}

void ZipLine::Tick()
{
}

void ZipLine::Render(HDC hdc)
{
}

void ZipLine::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void ZipLine::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
