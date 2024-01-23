#include "pch.h"
#include "ObjectManager.h"

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

void ObjectManager::Remove(Object* object)
{
}
