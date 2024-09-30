#pragma once
#include "Scene.h"

// 개발 확인용 클래스
class DevScene : public Scene
{
	using Super = Scene;

public:
	DevScene();
	virtual ~DevScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

