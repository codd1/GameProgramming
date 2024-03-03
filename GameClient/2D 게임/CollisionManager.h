#pragma once

class Collider;

// 등록을 받아서 모든 Collider 관리
class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);
public:
	void Init();
	void Update();

	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);

private:
	vector<Collider*> _colliders;
};

