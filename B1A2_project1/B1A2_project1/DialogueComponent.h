#pragma once
#include "Component.h"

class Dialogue;

class DialogueComponent : public Component
{
	using Super = Component;
public:
	DialogueComponent();
	virtual ~DialogueComponent() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

public:
	void SetDialogue(Dialogue* dialogue) { _dialogue = dialogue; }
	Dialogue* GetDialogue() { return _dialogue; }

	void SetShowDialogue(bool show) { _showDialogue = show; }
	bool GetShowDialogue() { return _showDialogue; }

private:
	Dialogue* _dialogue = nullptr;
	bool _showDialogue = false;
};

