#pragma once

class Component;
class Collider;
class DialogueComponent;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void BeginPlay();	// Init
	virtual void Tick();	// Update
	virtual void Render(HDC hdc);

	void SetPos(Vec2 pos) { _pos = pos; }
	Vec2 GetPos() { return _pos; }

	void SetID(int32 id) { _id = id; }
	int32 GetID() { return _id; }

	// 그리는 순서 Layer
	void SetLayer(LAYER_TYPE layer) { _layer = layer; }
	LAYER_TYPE GetLayer() { return _layer; }

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	// Collider
	Component* GetCollider();
	// OnCollisionEnter2D / OnCollisionExit2D
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

	// Dialogue
	DialogueComponent* GetDialogue();

protected:
	Vec2 _pos = { 100, 600 };
	Vec2 _destPos = { 0, 0 };
	int32 _id{};
	LAYER_TYPE _layer = {};
	std::vector<Component*> _components;
};

