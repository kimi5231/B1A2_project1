#include "pch.h"
#include "DialogueManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Dialogue.h"
#include "Actor.h"
#include "Player.h"
#include "GameObject.h"
#include "DialogueComponent.h"
#include "Scene.h"

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

	if (_isMove)
		Move();
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
			if (dynamic_cast<GameObject*>(actor))
			{
				// Actor Setting
				GameObject* object = dynamic_cast<GameObject*>(actor);
				object->SetState(static_cast<ObjectState>(_event[_eventCount].state));
				object->SetDir(static_cast<Dir>(_event[_eventCount].dir));
				// 객체가 대화 중 이동을 하는 경우 체크
				if (_event[_eventCount].posX > 0 || _event[_eventCount].posY > 0)
					StartMove(object);
				// DialogueComponent Setting
				_currentComponent = object->GetDialogue();
				_currentComponent->SetState(DialogueState::Running);
				if (_event[_eventCount].type == L"C")
				{
					_currentComponent->SetCurrentCutScene(_event[_eventCount].cutScene);
					_currentComponent->SetType(DialogueType::CutScene);
				}
				else if (_event[_eventCount].type == L"D")
					_currentComponent->SetType(DialogueType::Bubble);
				_currentComponent->SetSpeech(_event[_eventCount].speech);
			}

			continue;
		}

		// 대사에 맞는 객체가 아닐 때
		DialogueComponent* component = actor->GetDialogue();
		component->SetState(DialogueState::Hidden);
	}
}

void DialogueManager::StartMove(GameObject* object)
{
	_isMove = true;
	_movingObject = object;
}

void DialogueManager::EndMove()
{
	_isMove = false;
	_eventCount++;
	ChangeSpeech();
}

void DialogueManager::Move()
{
	if (_event[_eventCount].posX <= 0 && _event[_eventCount].posY <= 0)
		EndMove();
	
	if (!_isMove)
		return;
		
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();		

	float moveDis = 50 * deltaTime;
	Vec2 currentPos = _movingObject->GetPos();

	// Move
	if (_event[_eventCount].posX > 0)
	{
		if (_movingObject->GetDir() == DIR_RIGHT)
			_movingObject->SetPos({ currentPos.x + moveDis, currentPos.y });
		else
			_movingObject->SetPos({ currentPos.x - moveDis, currentPos.y });

		_event[_eventCount].posX -= moveDis;
	}

	if (_event[_eventCount].posY > 0)
	{
		if (_movingObject->GetDir() == DIR_DOWN)
			_movingObject->SetPos({ currentPos.x, currentPos.y + moveDis });
		else
			_movingObject->SetPos({ currentPos.x, currentPos.y - moveDis });

		_event[_eventCount].posY -= moveDis;
	}
}