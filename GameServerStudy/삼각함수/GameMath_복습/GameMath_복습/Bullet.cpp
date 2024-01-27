#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "FortressScene.h"
#include "SceneManager.h"
#include "ObjectManager.h"

Bullet::Bullet() : Object(ObjectType::Projectile)
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	_radius = 20.f;
}

// 81. Bullet::Update() 구현
void Bullet::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// Wind나 Gravity에 따른 업데이트도 여기서 구현

	_pos += _speed * deltaTime;

	// 화면을 크게 넘어갈 경우 (y좌표에 한해서) 다음 턴으로 넘어감
	if (_pos.y > GWinSizeX * 1.5 || _pos.y < -GWinSizeY * 1.5) {
		FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

		if (scene) {
			scene->ChangePlayerTurn();
		}

		GET_SINGLE(ObjectManager)->Remove(this);	// Bullet 객체 삭제
		return;
	}
}

// 82. Bullet::Render(HDC hdc) 구현
void Bullet::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, static_cast<int32>(_radius));
}
