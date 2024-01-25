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

	// 48. ������ ������ �߻�ǰ� ���� (����: �������θ� �߻�)
	//_pos.x += _stat.speed * deltaTime * ::cos(_angle);
	//_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

	// 50. �̻��� ����ź���� �����
	if (_target == nullptr) {	// Ÿ���� ���� ��� -> Ÿ���� �������ش�
		_pos.x += _stat.speed * deltaTime * ::cos(_angle);
		_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

		_sumTime += deltaTime;

		if (_sumTime >= 0.2f) {		// 0.2�ʰ� ������ �̻����� ����ź���� ����
			const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
			// ��� ���͸� �о ó�� ������ ���͸�
			for (Object* object : objects) {
				if (object->GetObjectType() == ObjectType::Monster) {
					_target = object;	// ����ź ���(Ÿ��)���� ����
					break;
				}
			}
		}
	}
	else {	// Ÿ���� �ִ� ���
		Vector dir = _target->GetPos() - GetPos();	// ��ǥ(����) ��ǥ���� �̻���(��)�� ��ǥ�� ����. (=����)
		dir.Length();
		dir.Normalize();	// "���⿡ ���� ����"�� ����. (ũ��=1)

		Vector moveDir = dir * _stat.speed * deltaTime;		// �̻����� �̵��ؾ��ϴ� ���� ����
		moveDir.Length();
		_pos += moveDir;
	}

	// 38. �̻��� �浹 ����
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects) {
		// ������Ʈ�� �ڱ� �ڽ��̸� ���� ������Ʈ�� �Ѿ
		if (object == this) {
			continue;
		}
		// ������Ʈ�� ���� ������ �ƴ� ��� ���� ������Ʈ�� �Ѿ
		// Object �����ڿ��� ObjectType�� �ʱ�ȭ �� ���༭ ��� object���� Ÿ���� ObjectType::None���� �Ǿ��ִ� ����...... (�̰��ϳ��� 30�� �ɷȴ� ��)
		if (object->GetObjectType() != ObjectType::Monster) {
			continue;
		}

		Pos p1 = GetPos();			// ��(�̻���)�� ��ġ
		Pos p2 = object->GetPos();	// ������Ʈ(����)�� ��ġ

		//const float dx = p1.x - p2.x;
		//const float dy = p1.y - p2.y;
		Vector dir = p2 - p1;

		// ��Ÿ��� ������ �̿��� dx^2 + dy^2�� ��Ʈ�� ����� �� = �ִܰŸ�
		//float dist = sqrt(dx * dx + dy * dy);
		float dist = dir.Length();

		if (dist < 25) {
			GET_SINGLE(ObjectManager)->Remove(object);	// ���� ����
			GET_SINGLE(ObjectManager)->Remove(this);	// ��(�̻���) ����
			return;		// ������ ��� ���� �߻�.... (���� �ְ� �ذ�)
		}
	}

	// �̻����� �ʹ� �־��� ��� ����
	if (_pos.y < -200) {
		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}
}

void Missile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 25);
}
