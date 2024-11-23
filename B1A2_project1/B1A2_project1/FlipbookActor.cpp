#include "pch.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "Texture.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ValueManager.h"

FlipbookActor::FlipbookActor()
{
}

FlipbookActor::~FlipbookActor()
{
}

void FlipbookActor::BeginPlay()
{
	Super::BeginPlay();
}

void FlipbookActor::Tick()
{
	Super::Tick();

	if (!_flipbook)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();
	if (info.loop == false && _idx == info.end)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_sumTime += deltaTime;		// 현재 애니메이션에 누적된 시간 업데이트

	int32 frameCount = (info.end - info.start + 1);		// 총 프레임 수 계산
	float delta = info.duration / frameCount;		// 각 프레임당 걸리는 시간

	if (_sumTime >= delta)		// 누적된 시간이 현재 프레임 유지 시간보다 크면
	{
		_sumTime = 0.f;
		_idx = (_idx + 1) % frameCount;
	}
}

void FlipbookActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (!_flipbook)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	::TransparentBlt(hdc,
		(int32)_pos.x - info.size.x / 2 - ((int32)cameraPos.x - winSize.x / 2),
		(int32)_pos.y - info.size.y / 2 - ((int32)cameraPos.y - winSize.y / 2),
		info.size.x,
		info.size.y,
		info.texture->GetDC(),
		(info.start + _idx) * info.size.x,
		info.line * info.size.y,
		info.size.x,
		info.size.y,
		info.texture->GetTransparent());
}

void FlipbookActor::SetFlipbook(Flipbook* flipbook)
{
	if (flipbook && _flipbook == flipbook)
		return;

	_flipbook = flipbook;
	Reset();
}

void FlipbookActor::Reset()
{
	_sumTime = 0.f;
	_idx = 0;
}
