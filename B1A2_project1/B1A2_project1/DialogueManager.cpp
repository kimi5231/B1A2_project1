#include "pch.h"
#include "DialogueManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Dialogue.h"
#include "Actor.h"
#include "Player.h"
#include "DialogueComponent.h"

DialogueManager::~DialogueManager()
{
	SAFE_DELETE(_dialogue);

	_event.clear();
}

void DialogueManager::Init()
{
	_isDialogue = false;
}

void DialogueManager::Update()
{
	if (!_isDialogue)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		if (_currentComponent->GetState() == DialogueState::Wait)
		{
			_eventCount++;

			if (_eventCount == _event.size())
				EndDialogue();
			else
				ChangeSpeech();
		}
		else if (_currentComponent->GetState() == DialogueState::Running)
		{
			const std::wstring& speech = _currentComponent->GetSpeech();
			_currentComponent->SetCurrentSpeech(speech);
		}
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::Tab) && (_sumTime >= 2.0f))
	{
		_sumTime = 0.f;
		EndDialogue();
	}
}

void DialogueManager::StartDialogue(const std::wstring& eventName, const std::vector<Actor*>& actors)
{
	_event = _dialogue->GetEvent(eventName);
	_actors = actors;

	_isDialogue = true;

	ChangeSpeech();
}

void DialogueManager::EndDialogue()
{
	for (Actor* actor : _actors)
	{
		DialogueComponent* component = actor->GetDialogue();
		component->SetState(DialogueState::Hidden);
	}

	_event.clear();

	_eventCount = 0;

	_isDialogue = false;
}

void DialogueManager::ChangeSpeech()
{
	for (Actor* actor : _actors)
	{
		// 대사에 맞는 객체 찾기
		if (_event[_eventCount].speakerID == actor->GetID())
		{
			// Actor Type에 따라 조건 추가 예정
			if (dynamic_cast<Player*>(actor))
			{
				// Actor Setting
				Player* player = dynamic_cast<Player*>(actor);
				player->SetState(static_cast<ObjectState>(_event[_eventCount].state));
				player->SetDir(static_cast<Dir>(_event[_eventCount].dir));
				// DialogueComponent Setting
				_currentComponent = player->GetDialogue();
				_currentComponent->SetState(DialogueState::Running);
				_currentComponent->SetSpeech(_event[_eventCount].speech);
			}

			continue;
		}

		// 대사에 맞는 객체가 아닐 때
		DialogueComponent* component = actor->GetDialogue();
		component->SetState(DialogueState::Hidden);
	}
}