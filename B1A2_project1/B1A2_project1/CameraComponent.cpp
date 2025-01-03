#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "SceneManager.h"
#include "ValueManager.h"

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::BeginPlay()
{
}

void CameraComponent::TickComponent()
{
	if (!_owner)
		return;

	Vec2 pos = _owner->GetPos();

	// TEMP
	// *맵 리소스 생성 되면, 맵 크기 변수로 수정 
	// 고민) 맵 크기에 따라 변수를 다르게 넣어줘야 하는데 if문으로 바꿔야 할까? (해결)

	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();
	Vec2Int mapSize = GET_SINGLE(ValueManager)->GetMapSize();

	pos.x = std::clamp(pos.x, (float)winSize.x / 2, (float)mapSize.x - (float)winSize.x / 2);	// const는 값을 변경하지 않겠다는 약속이지, 타입 변환을 막지 않음.
	pos.y = std::clamp(pos.y, (float)winSize.y / 2, (float)mapSize.y - (float)winSize.y / 2);

	GET_SINGLE(SceneManager)->SetCameraPos(pos);
}

void CameraComponent::Render(HDC hdc)
{
}
