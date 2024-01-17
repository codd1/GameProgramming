#include "pch.h"
#include "Actor.h"
#include "Component.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

// �Ź� �� ������ Actor�� å������ �ڱ����� ���� �ֵ鿡 ���� ó���� ���
void Actor::BeginPlay()
{
	for (Component* component : _components) {
		component->BeginPlay();
	}
}

void Actor::Tick()
{
	for (Component* component : _components) {
		component->TickComponent();
	}
}

void Actor::Render(HDC hdc)
{
	for (Component* component : _components) {
		component->Render(hdc);
	}
}

void Actor::AddComponent(Component* component)
{
	if (component == nullptr) {
		return;
	}

	component->SetOwner(this);
	_components.push_back(component);
}

void Actor::RemoveComponent(Component* component)
{
	auto findIter = std::find(_components.begin(), _components.end(), component);
	if (findIter == _components.end()) {
		return;
	}

	_components.erase(findIter);
}

void Actor::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void Actor::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
