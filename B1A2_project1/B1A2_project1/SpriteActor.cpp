#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "ValueManager.h"

SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::BeginPlay()
{
	Super::BeginPlay();
}

void SpriteActor::Tick()
{
	Super::Tick();
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (!_sprite)
		return;

	Vec2Int size = _sprite->GetSize();
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	::TransparentBlt(hdc,
		(((int32)_pos.x - size.x / 2) * ((float)winSize.x / (float)DefaultWinSizeX) - ((int32)cameraPos.x - winSize.x / 2)),
		(((int32)_pos.y - size.y / 2) * ((float)winSize.y / (float)DefaultWinSizeY) - ((int32)cameraPos.y - winSize.y / 2)),
		size.x * ((float)winSize.x / (float)DefaultWinSizeX),
		size.y * ((float)winSize.y / (float)DefaultWinSizeY),
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		_sprite->GetSize().x,
		_sprite->GetSize().y,
		_sprite->GetTransparent());
}
