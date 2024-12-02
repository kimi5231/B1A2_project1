#pragma once

class Collider;

// 지금은 생포인터지만 스마트 포인터로 사용해야 함
class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);

public:
	void Init();
	void Update();

	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);

private:
	std::vector<Collider*> _colliders;
};

