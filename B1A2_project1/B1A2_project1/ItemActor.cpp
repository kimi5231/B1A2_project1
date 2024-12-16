#include "pch.h"
#include "ItemActor.h"
#include "ResourceManager.h"

ItemActor::ItemActor(ItemType itemType)
{
	// Item
	if (itemType == ItemType::Key)
	{
		_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_keyInMap");
	}
	else if (itemType == ItemType::Pencil)
	{
		_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_pencilInMap");
	}
	else if (itemType == ItemType::Match)
	{
		_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_matchInMap");
	}

	// F_key
	_flipbookFKeyNoShow = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FkeyNoShow");
	_flipbookFKeyShow = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FkeyShow");

	SetFlipbook(_flipbookItemInMap);
}

ItemActor::~ItemActor()
{
}

void ItemActor::BeginPlay()
{
	Super::BeginPlay();
}

void ItemActor::Tick()
{
	Super::Tick();
}

void ItemActor::Render(HDC hdc)
{
	Super::Render(hdc);
}

void ItemActor::OnConponentBeginOverlap(Collider* collider, Collider* other)
{
}

void ItemActor::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
