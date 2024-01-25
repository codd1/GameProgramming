#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "ObjectManager.h"

Missile::Missile() : Object(ObjectType::Projectile)
{
}

Missile::~Missile()
{
}

void Missile::Init()
{
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;
}

void Missile::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 48. 포신의 방향대로 발사되게 수정 (기존: 위쪽으로만 발사)
	//_pos.x += _stat.speed * deltaTime * ::cos(_angle);
	//_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

	// 50. 미사일 유도탄으로 만들기
	if (_target == nullptr) {	// 타겟이 없는 경우 -> 타겟을 지정해준다
		_pos.x += _stat.speed * deltaTime * ::cos(_angle);
		_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

		_sumTime += deltaTime;

		if (_sumTime >= 0.2f) {		// 0.2초가 지나면 미사일이 유도탄으로 변신
			const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
			// 모든 몬스터를 읽어서 처음 읽히는 몬스터를
			for (Object* object : objects) {
				if (object->GetObjectType() == ObjectType::Monster) {
					_target = object;	// 유도탄 대상(타겟)으로 지정
					break;
				}
			}
		}
	}
	else {	// 타겟이 있는 경우
		Vector dir = _target->GetPos() - GetPos();	// 목표(몬스터) 좌표에서 미사일(나)의 좌표를 뺀다. (=벡터)
		dir.Length();
		dir.Normalize();	// "방향에 대한 정보"만 남음. (크기=1)

		Vector moveDir = dir * _stat.speed * deltaTime;		// 미사일이 이동해야하는 실제 벡터
		moveDir.Length();
		_pos += moveDir;
	}

	// 38. 미사일 충돌 구현
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects) {
		// 오브젝트가 자기 자신이면 다음 오브젝트로 넘어감
		if (object == this) {
			continue;
		}
		// 오브젝트가 몬스터 유형이 아닐 경우 다음 오브젝트로 넘어감
		// Object 생성자에서 ObjectType을 초기화 안 해줘서 모든 object들의 타입이 ObjectType::None으로 되어있던 문제...... (이거하나에 30분 걸렸다 ㅠ)
		if (object->GetObjectType() != ObjectType::Monster) {
			continue;
		}

		Pos p1 = GetPos();			// 나(미사일)의 위치
		Pos p2 = object->GetPos();	// 오브젝트(몬스터)의 위치

		//const float dx = p1.x - p2.x;
		//const float dy = p1.y - p2.y;
		Vector dir = p2 - p1;

		// 피타고라스 정리를 이용해 dx^2 + dy^2에 루트를 씌우는 것 = 최단거리
		//float dist = sqrt(dx * dx + dy * dy);
		float dist = dir.Length();

		if (dist < 25) {
			GET_SINGLE(ObjectManager)->Remove(object);	// 몬스터 제거
			GET_SINGLE(ObjectManager)->Remove(this);	// 나(미사일) 제거
			return;		// 리턴이 없어서 오류 발생.... (리턴 넣고 해결)
		}
	}

	// 미사일이 너무 멀어질 경우 삭제
	if (_pos.y < -200) {
		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}
}

void Missile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 25);
}
