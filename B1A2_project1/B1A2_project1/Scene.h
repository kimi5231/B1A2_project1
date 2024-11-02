#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene();	// 소멸자에 virtual 필수!!!

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
};