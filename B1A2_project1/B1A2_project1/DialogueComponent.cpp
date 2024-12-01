#include "pch.h"
#include "DialogueComponent.h"
#include "Dialogue.h"
#include "Actor.h"

DialogueComponent::DialogueComponent()
{
}

DialogueComponent::~DialogueComponent()
{
}

void DialogueComponent::BeginPlay()
{
}

void DialogueComponent::TickComponent()
{
}

void DialogueComponent::Render(HDC hdc)
{
	if (!_owner)
		return;

	std::vector<LineInfo>& event = _dialogue->GetEvent(L"test1");

	Utils::DrawString(hdc, _owner->GetPos(), event.begin()->speech);
}