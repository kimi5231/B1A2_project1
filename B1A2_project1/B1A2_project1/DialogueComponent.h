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
	void SetSpeech(const std::wstring& speech);
	const std::wstring& GetSpeech() { return _speech; }
	void SetCurrentSpeech(const std::wstring& speech) { _currentSpeech = speech; }

	void SetState(DialogueState state) { _state = state; }
	DialogueState GetState() { return _state; }

	Vec2Int GetDialogueRectSize(HDC hdc, const std::wstring& str);

private:
	std::wstring _speech;
	std::wstring _currentSpeech;
	int32 _speechCount = 0;
	DialogueState _state = DialogueState::Hidden;
	int32 _fontSize{};

	float _sumTime = 0.f;
};

