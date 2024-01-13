#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "FortressScene.h"

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

void Bullet::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// Wind

	// Gravity

	_pos += _speed * deltaTime;

	// 화면을 크게 넘어갈 경우(y)
	if (_pos.y > GWinSizeY * 1.5 || _pos.y < -GWinSizeY * 1.5) {
		FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		if (scene) {
			scene->ChangePlayerTurn();
		}

		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}

}

void Bullet::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, static_cast<int32>(_radius));
}
