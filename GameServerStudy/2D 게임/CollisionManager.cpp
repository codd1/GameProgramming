#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Actor.h"

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
	// �� ��ü�� ����������(�浹) Ȯ��
	// Collider�鳢�� �Ѿ� ¦ ��� �浹�ƴ��� Ȯ��
	vector<Collider*>& colliders = _colliders;

	for (int32 i = 0; i < colliders.size(); i++) {
		for (int32 j = i + 1; j < colliders.size(); j++) {
			Collider* src = colliders[i];
			Collider* dest = colliders[j];

			if (src->CheckCollision(dest)) {	// �浹�� �Ͼ ���
				// ó�� �浹�ϴ°��� üũ�ϴ� ������??
				// -> �� ���� ȣ���ϰ� �Ϸ���. �ƴϸ� �浹�Ǿ��ִ� ���� ��� ȣ��Ǵϱ�
				if (src->_collisionMap.contains(dest) == false) {	// ó�� �浹�ϴ� ����� ���
					src->GetOwner()->OnComponentBeginOverlap(src, dest);
					dest->GetOwner()->OnComponentBeginOverlap(dest, src);
					src->_collisionMap.insert(dest);
					dest->_collisionMap.insert(src);
				}
			}
			else {		// �浹�� �Ͼ�� ���� ���
				if (src->_collisionMap.contains(dest) == false) {	// ó�� �浹�ϴ� ����� ���
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
