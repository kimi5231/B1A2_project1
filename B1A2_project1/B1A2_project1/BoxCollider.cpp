#include "pch.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "ValueManager.h"
#include "Actor.h"
#include "SphereCollider.h"

BoxCollider::BoxCollider() : Collider(ColliderType::Box)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::BeginPlay()
{
	Super::BeginPlay();


}

void BoxCollider::TickComponent()
{
	Super::TickComponent();


}

void BoxCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();
	Vec2 pos = GetOwner()->GetPos();
	pos.x -= (cameraPos.x - winSize.x / 2);
	pos.y -= (cameraPos.y - winSize.y / 2);

	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawRect(hdc, pos, _size.x, _size.y);
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
	Vec2 pos = GetOwner()->GetPos();
	Vec2 size = GetSize();

	RECT rect =
	{
		(int32)(pos.x - (size.x / 2)),
		(int32)(pos.y - (size.y / 2)),
		(int32)(pos.x + (size.x / 2)),
		(int32)(pos.y + (size.y / 2))
	};

	return rect;
}
