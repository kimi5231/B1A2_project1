#pragma once
#include "Scene.h"

class TilemapScene : public Scene
{
	using Super = Scene;
public:
	TilemapScene();
	virtual ~TilemapScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

