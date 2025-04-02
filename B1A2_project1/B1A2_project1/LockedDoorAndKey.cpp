#include "pch.h"
#include "LockedDoorAndKey.h"
#include "ResourceManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "ValueManager.h"
#include "Texture.h"

LockedDoorAndKey::LockedDoorAndKey()
{
	// Flipbook
	_flipbookLockedDoor = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LockedDoor");
	_flipbookUnlockedDoor = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_UnlockedDoor");

	// Collider
	{
		// Detect
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_STRUCTURE_DETECT);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 160, 240 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
		
		// Structure
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_STRUCTURE);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 80, 240 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}


	SetState(ObjectState::Off);
}

LockedDoorAndKey::~LockedDoorAndKey()
{
}

void LockedDoorAndKey::BeginPlay()
{
	Super::BeginPlay();
}

void LockedDoorAndKey::Tick()
{
	Super::Tick();

	if (_isKeyAcquired)
		SetState(ObjectState::On);
}

void LockedDoorAndKey::Render(HDC hdc)
{
	Super::Render(hdc);

	// Key 그리기
	if (!_isKeyRender)
		return;
	
	// 보정 변수 가져오기
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	Vec2 cameraPosAdjustmemt = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();

	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LockedDoorItem");

	::TransparentBlt(hdc,
		_itemPos.x * winSizeAdjustmemt.x - cameraPosAdjustmemt.x,
		_itemPos.y * winSizeAdjustmemt.y - cameraPosAdjustmemt.y,
		texture->GetSize().x * winSizeAdjustmemt.x,
		texture->GetSize().y  * winSizeAdjustmemt.y,
		texture->GetDC(),
		0,
		0,
		texture->GetSize().x,
		texture->GetSize().y,
		texture->GetTransparent());

}

void LockedDoorAndKey::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::On:
		SetFlipbook(_flipbookUnlockedDoor);
		break;
	case ObjectState::Off:
		SetFlipbook(_flipbookLockedDoor);
	}
}

void LockedDoorAndKey::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		_isKeyRender = true;
	}
}

void LockedDoorAndKey::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
