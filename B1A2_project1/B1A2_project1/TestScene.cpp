#include "pch.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Sprite.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
	// BackGround
	//GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\UI\\Start.bmp");

	// Sprite
	GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Start");
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", tex, 150, 0, 150, 150);
}

void TestScene::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
}

void TestScene::Render(HDC hdc)
{
	Super::Render(hdc);

	//Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Stage01");
	Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Start_On");

	::BitBlt(hdc,
		0, 0,	// 시작하는 위치 (0, 0)
		GWinSizeX, GWinSizeY,
		sprite->GetDC(),
		sprite->GetPos().x, sprite->GetPos().y,	// 원래 텍스처의 위치 새로 지정함
		SRCCOPY);
}
