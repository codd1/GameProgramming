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
	if (findIter != _objects.end()) {		// �̹� �ִ� ���ϱ�
		return;								// ����
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

	// TODO: ��������?
	delete object;
}

void ObjectManager::Clear()
{
	std::for_each(_objects.begin(), _objects.end(), [=](Object* obj) { delete obj; });
	_objects.clear();
}
