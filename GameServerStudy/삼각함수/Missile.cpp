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
		if (_sumTime >= 0.2f) {		// 0.2�ʰ� ������ �̻����� ����ź���� ����
			// ��� ���͸� �о ó�� ������ ���͸� ����ź ������� ����
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
		Vector dir = _target->GetPos() - GetPos();		// ��ǥ(����) ��ǥ���� �̻���(��)�� ��ǥ�� ����. (=����)
		dir.Normalize();		// ���⿡ ���� ������ ���� (���� ũ�� 1)

		Vector moveDir = dir * _stat.speed * deltaTime;		// �̻����� �̵��ؾ��ϴ� ���� ���� (= �������� * �Ÿ�(ũ��))
		_pos += moveDir;
	}

	// �浹
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

		if (dist < 25) {	// ������ �¾��� ���
			// �ڡڡ� �̷� ������ �ڵ带 ¥�� �������� �׻� �����ؾ� ��.
			GET_SINGLE(ObjectManager)->Remove(object);	// ���� ����
			GET_SINGLE(ObjectManager)->Remove(this);	// ��(�̻���) ����
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
