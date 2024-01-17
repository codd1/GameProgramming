#include "pch.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Actor.h"

Collider::Collider(ColliderType colliderType) : _colliderType(colliderType)
{
}

Collider::~Collider()
{
}

void Collider::BeginPlay()
{
}

void Collider::TickComponent()
{
}

void Collider::Render(HDC hdc)
{
}

bool Collider::CheckCollision(Collider* other)
{
	return false;
}

bool Collider::CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2)
{
	Vec2 p1 = b1->GetOwner()->GetPos();
	Vec2 s1 = b1->GetSize();

	Vec2 p2 = b2->GetOwner()->GetPos();
	Vec2 s2 = b2->GetSize();

	float minX_1 = p1.x - s1.x / 2;
	float maxX_1 = p1.x + s1.x / 2;
	float minY_1 = p1.y - s1.y / 2;
	float maxY_1 = p1.y + s1.y / 2;

	float minX_2 = p2.x - s2.x / 2;
	float maxX_2 = p2.x + s2.x / 2;
	float minY_2 = p2.y - s2.y / 2;
	float maxY_2 = p2.y + s2.y / 2;

	// 극단적으로 안되는 case들을 구해서 제외시키고
	if (maxX_2 < minX_1)
		return false;

	if (maxX_1 < minX_2)
		return false;

	if (maxY_1 < minY_2)
		return false;

	if (maxY_2 < minY_1)
		return false;	

	// 위 4개의 조건 중에 없다면 충돌한걸로 판정
	return true;
}

bool Collider::CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2)
{
	return false;
}

bool Collider::CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2)
{
	// 원 두 개의 좌표를 가져와서 각 원의 radius를 더한 뒤,
	// 그게 실제로 두 물체 사이의 거리보다 작은지 판별 (작으면 충돌)
	Vec2 p1 = s1->GetOwner()->GetPos();
	float r1 = s1->GetRadius();

	Vec2 p2 = s2->GetOwner()->GetPos();
	float r2 = s2->GetRadius();

	Vec2 dir = p1 - p2;
	float dist = dir.Length();

	return dist <= r1 + r2;

}
