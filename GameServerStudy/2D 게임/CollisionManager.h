#pragma once

class Collider;

// ����� �޾Ƽ� ��� Collider ����
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

