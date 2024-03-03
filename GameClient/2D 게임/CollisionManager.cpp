#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Actor.h"

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
	// 두 물체가 포개졌는지(충돌) 확인
	// Collider들끼리 둘씩 짝 지어서 충돌됐는지 확인
	vector<Collider*>& colliders = _colliders;

	for (int32 i = 0; i < colliders.size(); i++) {
		for (int32 j = i + 1; j < colliders.size(); j++) {
			Collider* src = colliders[i];
			Collider* dest = colliders[j];

			if (src->CheckCollision(dest)) {	// 충돌이 일어난 경우
				// 처음 충돌하는건지 체크하는 이유는??
				// -> 한 번만 호출하게 하려고. 아니면 충돌되어있는 동안 계속 호출되니까
				if (src->_collisionMap.contains(dest) == false) {	// 처음 충돌하는 요소일 경우
					src->GetOwner()->OnComponentBeginOverlap(src, dest);
					dest->GetOwner()->OnComponentBeginOverlap(dest, src);
					src->_collisionMap.insert(dest);
					dest->_collisionMap.insert(src);
				}
			}
			else {		// 충돌이 일어나지 않은 경우
				if (src->_collisionMap.contains(dest) == false) {	// 처음 충돌하는 요소일 경우
					src->GetOwner()->OnComponentEndOverlap(src, dest);
					dest->GetOwner()->OnComponentEndOverlap(dest, src);
					src->_collisionMap.erase(dest);
					dest->_collisionMap.erase(src);
				}
			}
		}
	}
}

void CollisionManager::AddCollider(Collider* collider)
{
	_colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider)
{
	auto iter = std::remove(_colliders.begin(), _colliders.end(), collider);
	_colliders.erase(iter, _colliders.end());
}
