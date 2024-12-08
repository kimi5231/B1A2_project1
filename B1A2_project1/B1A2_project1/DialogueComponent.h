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
	void SetSpeech(const std::wstring& speech) { _speech = speech; }
	//std::wstring GetSpeech() { return _speech; }

	void SetShowDialogue(bool show) { _showDialogue = show; }
	bool GetShowDialogue() { return _showDialogue; }

	Vec2Int GetDialogueRectSize(HDC hdc, const std::wstring& str);

private:
	std::wstring _speech;
	bool _showDialogue = false;
	int32 _fontSize{};
};

