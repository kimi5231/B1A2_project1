#include "pch.h"
#include "FlipbookUI.h"
#include "Flipbook.h"
#include "Texture.h"
#include "TimeManager.h"

FlipbookUI::FlipbookUI()
{
}

FlipbookUI::~FlipbookUI()
{
}

void FlipbookUI::BeginPlay()
{
	Super::BeginPlay();
}

void FlipbookUI::Tick()
{
	Super::Tick();

	if (_flipbook == nullptr)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();
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

void FlipbookUI::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_flipbook == nullptr)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();

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

void FlipbookUI::SetFilpbook(Flipbook* flipbook)
{
	if (flipbook == nullptr)
		return;

	_flipbook = flipbook;
	Reset();
}

void FlipbookUI::Reset()
{
	_sumTime = 0.f;
	_idx = 0;
}