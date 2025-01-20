#include "pch.h"
#include "InGameUI.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "ValueManager.h"

InGameUI::InGameUI()
{
}

InGameUI::~InGameUI()
{
}

void InGameUI::BeginPlay()
{
	Super::BeginPlay();

	// InGame UI Texture Load
	GET_SINGLE(ResourceManager)->LoadTexture(L"HpBar", L"Sprite\\UI\\HpBar.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"HpPoint", L"Sprite\\UI\\HpPoint.bmp", RGB(55, 255, 0));

}

void InGameUI::Tick()
{
	Super::Tick();
}

void InGameUI::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	//{
	//	Texture* hpBar = GET_SINGLE(ResourceManager)->GetTexture(L"HpBar");
	//	::TransparentBlt(hdc,
	//		::TransparentBlt(hdc,
	//			10 * winSizeAdjustmemt.x,
	//			10 * winSizeAdjustmemt.y,
	//			hpBar->GetSize().x * winSizeAdjustmemt.x,
	//			hpBar->GetSize().y * winSizeAdjustmemt.y,
	//			hpBar->GetDC(),
	//			0,
	//			0,
	//			hpBar->GetSize().x,
	//			hpBar->GetSize().y,
	//			hpBar->GetTransparent());
	//}
} 
