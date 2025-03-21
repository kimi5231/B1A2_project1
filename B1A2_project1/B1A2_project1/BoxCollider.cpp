#include "pch.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "SceneManager.h"
#include "ValueManager.h"
#include "Actor.h"
#include "TilemapActor.h"
#include "Monster.h"

BoxCollider::BoxCollider() : Collider(ColliderType::Box)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::BeginPlay()
{
	Super::BeginPlay();

	if (!dynamic_cast<TilemapActor*>(GetOwner()))
		_pos = GetOwner()->GetPos();
	
	if (GetCollisionLayer() == CLT_DETECT && dynamic_cast<Monster*>(GetOwner()))
	{
		Monster* owner = dynamic_cast<Monster*>(GetOwner());
		Vec2Int playerDetection = owner->GetPlayerDetection();

		if(owner->GetDir() == DIR_RIGHT)
			_pos.x = owner->GetPos().x + playerDetection.x / 2;
		else
			_pos.x = owner->GetPos().x - playerDetection.x / 2;
	}
}

void BoxCollider::TickComponent()
{
	Super::TickComponent();

	if (!dynamic_cast<TilemapActor*>(GetOwner()))
		_pos = GetOwner()->GetPos();

	if (GetCollisionLayer() == CLT_DETECT && dynamic_cast<Monster*>(GetOwner()))
	{
		Monster* owner = dynamic_cast<Monster*>(GetOwner());
		Vec2Int playerDetection = owner->GetPlayerDetection();
		
		if (owner->GetDir() == DIR_RIGHT)
			_pos.x = owner->GetPos().x + playerDetection.x / 2;
		else
			_pos.x = owner->GetPos().x - playerDetection.x / 2;
	}
}

void BoxCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2 cameraPosAdjustment = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();
	Vec2 winSizeAdjustment = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawRect(hdc, 
		{ _pos.x * winSizeAdjustment.x - cameraPosAdjustment.x,
		_pos.y * winSizeAdjustment.y - cameraPosAdjustment.y },
		_size.x * winSizeAdjustment.x,
		_size.y* winSizeAdjustment.y);
	::SelectObject(hdc, oldBrush);
	::DeleteObject(myBrush);
}

bool BoxCollider::CheckCollision(Collider* other)
{
	if (Super::CheckCollision(other) == false)		// 애초에 충돌을 원하지 않으면 바로 skip
		return false;

	switch (other->GetColliderType())
	{
	case ColliderType::Box:
		return CheckCollisionBox2Box(this, static_cast<BoxCollider*>(other));
	case ColliderType::Sphere:
		return CheckCollisionSphere2Box(static_cast<SphereCollider*>(other), this);
	}

	return false;
}

RECT BoxCollider::GetRect()
{
	RECT rect =
	{
		(int32)(_pos.x - (_size.x / 2)),
		(int32)(_pos.y - (_size.y / 2)),
		(int32)(_pos.x + (_size.x / 2)),
		(int32)(_pos.y + (_size.y / 2))
	};

	return rect;
}
