#include "pch.h"
#include "CameraActor.h"
#include "InputManager.h"
#include "TimeManager.h"
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
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		_pos.y -= 1000 * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= 1000 * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_pos.y += 1000 * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += 1000 * deltaTime;
	}

	Super::Tick();
}

void CameraActor::Render(HDC hdc)
{
	Super::Render(hdc);

	Utils::DrawRect(hdc, _pos, {100, 100});
}