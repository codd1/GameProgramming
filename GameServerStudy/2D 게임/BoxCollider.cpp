#include "pch.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "Actor.h"
#include "SphereCollider.h"

BoxCollider::BoxCollider(): Collider(ColliderType::Box)
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::BeginPlay()
{
	Super::BeginPlay();
}

void BoxCollider::TickComponent()
{
	Super::TickComponent();
}

void BoxCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2 pos = GetOwner()->GetPos();

	// 카메라가 중앙을 보게 하기 위한 설정 (나머지를 반대방향으로 보냄)
	pos.x -= (cameraPos.x - GWinSizeX / 2);
	pos.y -= (cameraPos.y - GWinSizeY / 2);

	// HBRUSH는 사각형(충돌 범위)을 투명색으로 하기 위함
	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawRect(hdc, pos, _size.x, _size.y);
	::SelectObject(hdc, oldBrush);
	::DeleteObject(myBrush);
}

bool BoxCollider::CheckCollision(Collider* other)
{
	switch (other->GetColliderType())
	{
	case ColliderType::Box:
		return CheckCollisionBox2Box(this, static_cast<BoxCollider*>(other));
	case ColliderType::Sphere:
		return CheckCollisionSphere2Box(static_cast<SphereCollider*>(other), this);
	}

	return false;
}
