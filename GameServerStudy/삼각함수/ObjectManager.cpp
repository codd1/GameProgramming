#include "pch.h"
#include "ObjectManager.h"
#include "Object.h"

ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::Add(Object* object)
{
	if (object == nullptr) {
		return;
	}

	auto findIter = std::find(_objects.begin(), _objects.end(), object);
	if (findIter != _objects.end()) {		// 이미 있는 경우니까
		return;								// 무시
	}

	_objects.push_back(object);
}

void ObjectManager::Remove(Object* object)
{
	if (object == nullptr) {
		return;
	}

	auto findIter = std::remove(_objects.begin(), _objects.end(), object);
	_objects.erase(findIter, _objects.end());

	// TODO: 괜찮을까?
	delete object;
}

void ObjectManager::Clear()
{
	std::for_each(_objects.begin(), _objects.end(), [=](Object* obj) { delete obj; });
	_objects.clear();
}
