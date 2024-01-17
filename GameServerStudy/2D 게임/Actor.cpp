#include "pch.h"
#include "Actor.h"
#include "Component.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

// 매번 돌 때마다 Actor가 책임지고 자기한테 딸린 애들에 대한 처리도 담당
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
