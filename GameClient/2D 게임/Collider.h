#pragma once
#include "Component.h"

class BoxCollider;
class SphereCollider;

// 충돌 여부 판별
class Collider : public Component
{
public:
	Collider(ColliderType colliderType);
	virtual ~Collider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);

	ColliderType GetColliderType() { return _colliderType; }
	void SetShowDebug(bool show) { _showDebug = show; }

public:
	static bool CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2);
	static bool CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2);
	static bool CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2);

protected:
	ColliderType _colliderType;
	bool _showDebug = true;

public:
	// 이미 나와 한 번 충돌한 애들 (메모)
	unordered_set<Collider*> _collisionMap;
};

