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

	// std::find �Լ��� ����Ͽ� ���� _objects���� Ư�� ��ü object�� ã��
	// object�� _objects�� �����Ѵٸ� findIter�� �ش� ���Ҹ� ����Ű�� �ݺ��ڰ� �ȴ�.
	// ����, object�� _objects�� �������� �ʴ´ٸ� findIter�� _objects.end()�� ����Ű�� �ݺ��ڰ� �ȴ�.
	auto findIter = std::find(_objects.begin(), _objects.end(), object);
	if (findIter != _objects.end()) {
		return;
	}

	_objects.push_back(object);
}

// 39. ObjectManager::Remove ���� - �̻���, ���� Remove ����
void ObjectManager::Remove(Object* object)
{
	if (object == nullptr) {
		return;
	}

	auto findIter = remove(_objects.begin(), _objects.end(), object);	// #include <algorithm>
	_objects.erase(findIter, _objects.end());

	delete object;
}

void ObjectManager::Clear()
{
	// for_each: 1�� ���ں��� 2�� ���� ���� ������ 3�� ���ڸ� ����
	// Lambda �Լ�
	for_each(_objects.begin(), _objects.end(), [=](Object* obj) { delete obj; });
	_objects.clear();
}
