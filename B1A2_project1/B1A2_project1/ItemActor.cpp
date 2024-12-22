#include "pch.h"
#include "ItemActor.h"
#include "ResourceManager.h"
#include "ValueManager.h"
#include "Flipbook.h"
#include "FlipbookActor.h"
#include "SceneManager.h"
#include "Texture.h"
#include "BoxCollider.h"

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
	_flipbookFKey = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Fkey");

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

	// F key
	if (_FkeyState == FKeyState::Hidden)
		return;

	// 보정 변수 가져오기
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	Vec2 cameraPosAdjustmemt = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();

	// F key 위치 지정
	Vec2 ItemPos = _pos * winSizeAdjustmemt - cameraPosAdjustmemt;
	Vec2 pos = { ItemPos.x - 15.f, ItemPos.y - 70.f };
	RECT rect = { pos.x, pos.y, pos.x + 30, pos.y + 30 };

	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"F_key");
	::TransparentBlt(hdc,
		pos.x,
		pos.y,
		30,
		30,
		texture->GetDC(),
		0,
		0,
		texture->GetSize().x,
		texture->GetSize().y,
		texture->GetTransparent());
}

void ItemActor::OnConponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	SetFKeyState(FKeyState::Show);
}

void ItemActor::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
