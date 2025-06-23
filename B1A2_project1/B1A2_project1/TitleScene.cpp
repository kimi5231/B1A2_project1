#include "pch.h"
#include "TitleScene.h"
#include "TitlePanel.h"
#include "Button.h"
#include "Flipbook.h"
#include "Sprite.h"
#include "SpriteActor.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{
	TitlePanel* panel = new TitlePanel();
	panel->SetOwner(this);
	AddPanel(panel);

	LoadUI();

	_sceneState = SceneState::Title;

	Super::Init();
}

void TitleScene::Update()
{
	SetSceneState();

	if (_sceneState == SceneState::Title)
	{
		Super::Update();
	}
	else if (_sceneState == SceneState::SelectStart)
	{
		if (_beginContinuePanel)
			_beginContinuePanel->Tick();
	}
}

void TitleScene::Render(HDC hdc)
{
	if (_sceneState == SceneState::Title)
	{
		Super::Render(hdc);
	}
	else if (_sceneState == SceneState::SelectStart)
	{
		if (_beginContinuePanel)
			_beginContinuePanel->Render(hdc);
	}
}

void TitleScene::OnClickBegin()
{
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::GameScene);
}

void TitleScene::OnClickContinue()
{
}

void TitleScene::SetSceneState()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Esc))
	{
		if (_sceneState == SceneState::Title)
			return;
		
		if (_sceneState == SceneState::SelectStart)
		{
			_sceneState = SceneState::Title;
		}
	}
}

void TitleScene::LoadUI()
{
	// Menu
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"Begin", L"Sprite\\UI\\Begin.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"Continue", L"Sprite\\UI\\Continue.bmp", RGB(55, 255, 0));

		_beginContinuePanel = new Panel();
	}

	// Begin
	{
		Button* button = new Button();

		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Begin");

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BeginDefault");
			fb->SetInfo({ texture, L"FB_BeginDefalt", {163, 60}, 0, 0, 0, 0.5f, false });
			button->SetFlipbook(fb, BS_Default);
		}

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BeginHovered");
			fb->SetInfo({ texture, L"FB_BeginHovered", {163, 60}, 0, 3, 1, 0.5f, true });
			button->SetFlipbook(fb, BS_Hovered);
		}

		button->SetPos({ 540, 360 });
		button->SetSize({ 163, 60 });
		button->AddOnClickDelegate(this, &TitleScene::OnClickBegin);
		_beginContinuePanel->AddChild(button);
	}

	// Continue
	{
		Button* button = new Button();

		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Continue");

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ContinueDefault");
			fb->SetInfo({ texture, L"FB_ContinueDefalt", {163, 60}, 0, 0, 0, 0.5f, false });
			button->SetFlipbook(fb, BS_Default);
		}

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ContinueHover");
			fb->SetInfo({ texture, L"FB_ContinueHovered", {163, 60}, 0, 3, 1, 0.5f, true });
			button->SetFlipbook(fb, BS_Hovered);
		}


		button->SetPos({ 740, 360 });
		button->SetSize({ 163, 60 });

		button->AddOnClickDelegate(this, &TitleScene::OnClickContinue);
		_beginContinuePanel->AddChild(button);
	}

	// Background
	{
		Texture* texture = GET_SINGLE(ResourceManager)->LoadTexture(L"Background", L"Sprite\\UI\\TitleBackground.bmp");
		GET_SINGLE(ResourceManager)->CreateSprite(L"Background", texture, 0, 0, 1280, 720);
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Background");

		const Vec2Int size = sprite->GetSize();
		SpriteActor* background = new SpriteActor();
		background->SetLayer(LAYER_BACKGROUND);
		background->SetPos(Vec2(size.x / 2, size.y / 2));
		background->SetSprite(sprite);

		AddActor(background);
	}
}