#pragma once

class Panel;
class Actor;
class Player;
class Inventory;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

protected:
	Panel* _panel = nullptr;
	std::vector<Actor*> _actors[LAYER_MAXCOUNT];

	Inventory* _inventory = nullptr;

	SceneState _sceneState = SceneState::Play;
};