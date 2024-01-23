#include "pch.h"
#include "ObjectManager.h"

void ObjectManager::Add(Object* object)
{
	if (object == nullptr) {
		return;
	}

	// std::find 함수를 사용하여 벡터 _objects에서 특정 객체 object를 찾음
	// object가 _objects에 존재한다면 findIter는 해당 원소를 가리키는 반복자가 된다.
	// 만약, object가 _objects에 존재하지 않는다면 findIter는 _objects.end()를 가리키는 반복자가 된다.
	auto findIter = std::find(_objects.begin(), _objects.end(), object);
	if (findIter != _objects.end()) {
		return;
	}

	_objects.push_back(object);
}

void ObjectManager::Remove(Object* object)
{
}
