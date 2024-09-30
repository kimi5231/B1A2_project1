#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene();	// 소멸자에 virtual 필수!!!

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;
};

