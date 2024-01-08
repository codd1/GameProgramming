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

	if (_target == nullptr) {
		_pos.x += _stat.speed * deltaTime * ::cos(_angle);
		_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

		_sumTime += deltaTime;
		if (_sumTime >= 0.2f) {		// 0.2초가 지나면 미사일이 유도탄으로 변신
			// 모든 몬스터를 읽어서 처음 읽히는 몬스터를 유도탄 대상으로 지정
			const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
			for (Object* object : objects) {
				if (object->GetObjectType() == ObjectType::Monster) {
					_target = object;
					break;
				}
			}
		}
	}
	else {
		Vector dir = _target->GetPos() - GetPos();		// 목표(몬스터) 좌표에서 미사일(나)의 좌표를 뺀다. (=벡터)
		dir.Normalize();		// 방향에 대한 정보만 유지 (벡터 크기 1)

		Vector moveDir = dir * _stat.speed * deltaTime;		// 미사일이 이동해야하는 실제 벡터 (= 방향정보 * 거리(크기))
		_pos += moveDir;
	}

	// 충돌
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects) {
		if (object == this) {
			continue;
		}

		if (object->GetObjectType() != ObjectType::Monster) {
			continue;
		}

		Vector p1 = GetPos();
		Vector p2 = object->GetPos();

		Vector dir = p2 - p1;
		float dist = dir.Length();

		if (dist < 25) {	// 누군가 맞았을 경우
			// ★★★ 이런 식으로 코드를 짜도 괜찮을지 항상 생각해야 함.
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
