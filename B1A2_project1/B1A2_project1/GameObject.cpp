#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::BeginPlay()
{
}

void GameObject::Tick()
{
}

void GameObject::Render(HDC hdc)
{
}

void GameObject::SetState(ObjectState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void GameObject::SetDir(Dir dir)
{
	_dir = dir;
	UpdateAnimation();
}