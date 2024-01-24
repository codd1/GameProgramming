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

	// std::find 함수를 사용하여 벡터 _objects에서 특정 객체 object를 찾음
	// object가 _objects에 존재한다면 findIter는 해당 원소를 가리키는 반복자가 된다.
	// 만약, object가 _objects에 존재하지 않는다면 findIter는 _objects.end()를 가리키는 반복자가 된다.
	auto findIter = std::find(_objects.begin(), _objects.end(), object);
	if (findIter != _objects.end()) {
		return;
	}

	_objects.push_back(object);
}

// 39. ObjectManager::Remove 구현 - 미사일, 몬스터 Remove 구현
void ObjectManager::Remove(Object* object)
{
	if (object == nullptr) {
		return;
	}

	auto findIter = remove(_objects.begin(), _objects.end(), object);	// #include <algorithm>
	
	// TODO: 아래 조건이 없는 경우 오류 발생!!! -> why?
	if (findIter == _objects.end()) {	// 범위 내에 object가 없는 경우 
		return;
	}

	// object = 5
	// [ 1, 2, 3, 5, 5 ] --remove--> [ 1, 2, 3,v 5, 5 ] --erase--> [ 1, 2, 3 ]
	_objects.erase(findIter, _objects.end());

	delete object;
}

void ObjectManager::Clear()
{
	// for_each: 1번 인자부터 2번 인자 범위 내에서 3번 인자를 수행
	// Lambda 함수
	for_each(_objects.begin(), _objects.end(), [=](Object* obj) { delete obj; });
	_objects.clear();
}
