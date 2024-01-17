#include "pch.h"
#include "SphereCollider.h"
#include "SceneManager.h"
#include "Actor.h"
#include "BoxCollider.h"

SphereCollider::SphereCollider(): Collider(ColliderType::Sphere)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::BeginPlay()
{
	Super::BeginPlay();
}

void SphereCollider::TickComponent()
{
	Super::TickComponent();
}

void SphereCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_showDebug == false) {
		return;
	}

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2 pos = GetOwner()->GetPos();

	// 카메라가 중앙을 보게 하기 위한 설정 (나머지를 반대방향으로 보냄)
	pos.x -= (cameraPos.x - GWinSizeX / 2);
	pos.y -= (cameraPos.y - GWinSizeY / 2);

	// HBRUSH는 원(충돌 범위)을 투명색으로 하기 위함
	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawCircle(hdc, pos, _radius);
	::SelectObject(hdc, oldBrush);
	::DeleteObject(myBrush);
}

bool SphereCollider::CheckCollision(Collider* other)
{
	switch (other->GetColliderType())
	{
	case ColliderType::Box:
		return CheckCollisionSphere2Box(this, static_cast<BoxCollider*>(other));
	case ColliderType::Sphere:
		return CheckCollisionSphere2Sphere(this, static_cast<SphereCollider*>(other));
	}

	return false;
}
