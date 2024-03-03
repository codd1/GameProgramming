#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "FortressScene.h"
#include "UIManager.h"

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
	float windPercent = GET_SINGLE(UIManager)->GetWindPercent();
	_speed.x += 20 * deltaTime * windPercent;

	// Gravity
	Vector gravity{ 0, 1000 * deltaTime };		// 중력가속도*시간
	_speed += gravity;			// y는 아래로 가는게 양수

	// 총알 이동
	_pos += _speed * deltaTime;

	// 충돌
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects) {
		if (object->GetObjectType() != ObjectType::Player) {
			continue;
		}
		if (object == _owner) {		// 본인이 쏜 총알에 본인이 맞을 경우
			continue;
		}

		// 상대가 총알을 맞은 경우
		Vector dir = _pos - object->GetPos();
		if (dir.Length() < _radius + object->GetRadius()) {
			FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
			if (scene) {
				scene->ChangePlayerTurn();
			}

			GET_SINGLE(ObjectManager)->Remove(this);
			return;
		}
	}

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
