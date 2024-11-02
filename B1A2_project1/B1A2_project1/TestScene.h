#pragma once
#include "Scene.h"

class TestScene : public Scene
{
	using Super = Scene;

public:
	TestScene();
	virtual ~TestScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

