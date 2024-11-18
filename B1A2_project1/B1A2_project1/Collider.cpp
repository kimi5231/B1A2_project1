#include "pch.h"
#include "Collider.h"

Collider::Collider(ColliderType colliderType) : _colliderType(colliderType)
{
}

Collider::~Collider()
{
}

void Collider::BeginPlay()
{
}

void Collider::TickComponent()
{
}

void Collider::Render(HDC hdc)
{
}

bool Collider::CheckCollision(Collider* other)
{
	uint8 layer = other->GetCollisionLayer();
	if (_collisionFlag & (1 << layer))		// 내 flag에서 상대방 것이 켜져 있는가 확인
		return true;

	return false;
}

void Collider::AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag |= (1 << layer);		// | : 비트 켜기
}

void Collider::RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag &= ~(1 << layer);	// &~ : 비트 끄기
}
