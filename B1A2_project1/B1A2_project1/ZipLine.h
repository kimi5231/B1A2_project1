#pragma once
#include "Structure.h"

class ZipLine : public Structure
{
	using Super = Structure;
public:
	ZipLine(ZipLineType zipLineType);
	virtual ~ZipLine() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

private:
	Flipbook* _flipbookZipLine = nullptr;
	Flipbook* _flipbookButton = nullptr;
	Flipbook* _flipbookDisplay = nullptr;
};

