#pragma once

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

public:
	void ChangeScene(SceneType sceneType);	// 원하는 Scene으로 바꿈

private:
	class Scene* _scene;	// 현재 실행하고 있는 Scene
	SceneType _sceneType = SceneType::None;
};

