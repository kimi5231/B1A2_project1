#include "pch.h"
#include "CameraActor.h"
#include "InputManager.h"
#include "CameraComponent.h"
#include "Component.h"

CameraActor::CameraActor()
{
	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);
}

CameraActor::~CameraActor()
{
}

void CameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void CameraActor::Tick()
{
	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_pos.y += 100;
	}

	Super::Tick();
}

void CameraActor::Render(HDC hdc)
{
	Super::Render(hdc);

	Utils::DrawRect(hdc, _pos, {100, 100});
}