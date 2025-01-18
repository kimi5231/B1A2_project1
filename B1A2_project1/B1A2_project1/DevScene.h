#pragma once
#include "Scene.h"	// 상속 받으면 전방 선언 의미 없으므로, 무조건 include로 상속 객체 받아야 함.

class DevScene : public Scene
{
	using Super = Scene;

public:
	DevScene();
	virtual ~DevScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void LoadMap();
	void LoadPlayer();
	void LoadDialogue();
	void LoadItem();
	void LoadInventory();
	void LoadMenu();
	void LoadSound();

public:
	void SetSceneState();	// ESC 입력으로 Menu
	
	// Menu
	void OnClickGoTitleButton();
	void OnClickMenuButton();
	void OnClickSettingButton();

private:
	Panel* _menuPanel = nullptr;	// Menu 상태에서만 보여야 해서 _panel과 별개로 변수 생성
};
