#include "pch.h"
#include "ItemActor.h"
#include "ResourceManager.h"

ItemActor::ItemActor(ItemType itemType)
{
	if (itemType == ItemType::Key)
	{
		_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_keyInMap");
		SetFlipbook(_flipbookItemInMap);
	}
	/*else if (itemType == ItemType::Pencil)
	{
		_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetSprite(L"1002_pencil_inMap");
	}
	else if (itemType == ItemType::Match)
	{
		_flipbookItemInMap = GET_SINGLE(ResourceManager)->GetSprite(L"1003_match_inMap");
	}*/
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
