#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "ObjectManager.h"

Missile::Missile() : Object(ObjectType::Projectile)
{
}

Missile::~Missile()
{
}

void Missile::Init()
{
	// TODO: Data
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;
}

void Missile::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_pos.x += _stat.speed * deltaTime * ::cos(_angle);
	_pos.y -= _stat.speed * deltaTime * ::sin(_angle);
	//_pos.y -= deltaTime * _stat.speed;

	// 충돌
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects) {
		if (object == this) {
			continue;
		}

		if (object->GetObjectType() != ObjectType::Monster) {
			continue;
		}

		Pos p1 = GetPos();
		Pos p2 = object->GetPos();

		const float dx = p1.x - p2.x;
		const float dy = p1.y - p2.y;
		float dist = sqrt(dx * dx + dy * dy);

		if (dist < 25) {	// 누군가 맞았을 경우
			GET_SINGLE(ObjectManager)->Remove(object);	// 몬스터 제거
			GET_SINGLE(ObjectManager)->Remove(this);	// 나(미사일) 제거
			return;
		}
	}

	// TODO
	if (_pos.y < -200) {
		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}
}

void Missile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 25);
}
