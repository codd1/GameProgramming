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
	Vector gravity{ 0, 1000 * deltaTime };		// �߷°��ӵ�*�ð�
	_speed += gravity;			// y�� �Ʒ��� ���°� ���

	// �Ѿ� �̵�
	_pos += _speed * deltaTime;

	// �浹
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects) {
		if (object->GetObjectType() != ObjectType::Player) {
			continue;
		}
		if (object == _owner) {		// ������ �� �Ѿ˿� ������ ���� ���
			continue;
		}

		// ��밡 �Ѿ��� ���� ���
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

	// ȭ���� ũ�� �Ѿ ���(y)
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
