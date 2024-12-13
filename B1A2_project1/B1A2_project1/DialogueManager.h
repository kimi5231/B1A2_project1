#pragma once
#include "Dialogue.h"

class Actor;
class DialogueComponent;

// Actor들의 대화를 관리하는 클래스
class DialogueManager
{
public:
	DECLARE_SINGLE(DialogueManager);

	~DialogueManager();

public:
	void Init();
	void Update();

public:
	void SetDialogue(Dialogue* dialogue) { _dialogue = dialogue; }

public:
	void StartDialogue(const std::wstring& eventName, const std::vector<Actor*>& actors);
	void EndDialogue();

	void ChangeSpeech();

private:
	Dialogue* _dialogue{};
	std::vector<LineInfo> _event;
	int32 _eventCount = 0;
	std::vector<Actor*> _actors;
	DialogueComponent* _currentComponent;
	bool _isDialogue = false;

	float _sumTime = 0.f;
};

