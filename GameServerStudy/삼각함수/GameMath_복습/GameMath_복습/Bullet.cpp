#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "FortressScene.h"
#include "SceneManager.h"
#include "ObjectManager.h"
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

// 81. Bullet::Update() ����
void Bullet::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// Wind�� Gravity�� ���� ������Ʈ�� ���⼭ ����
	// 87. Wind
	float windPercent = GET_SINGLE(UIManager)->GetWindPercent();
	_speed.x += 20 * deltaTime * windPercent;

	// 88. Gravity
	Vector gravity{ 0, 1000 * deltaTime };		// �߷��̹Ƿ� y�� ���� ����
	_speed += gravity;

	_pos += _speed * deltaTime;


	// 89. �浹 ���� + _owner ������� ����
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();

	for (Object* object : objects) {
		if (object->GetObjectType() != ObjectType::Player) {
			continue;
		}

		if (object == _owner) {		// �ڱⰡ �� �̻��Ͽ� ���� ���
			continue;
		}

		Vector dir = _pos - object->GetPos();	// Player ��ǥ -> �̻��� ��ǥ ����
		
		// ��밡 ���� ���
		// Player�� �̻��� ������ �Ÿ� < �̻��� ������ + Player �������� ũ��
		if (dir.Length() < _radius + object->GetRadius()) {
			FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
			if (scene) {
				scene->ChangePlayerTurn();		// ��� ������ �Ѿ��.
			}

			GET_SINGLE(ObjectManager)->Remove(this);	// �̻��� ��ü ����
			return;
		}
	}


	// ȭ���� ũ�� �Ѿ ��� (y��ǥ�� ���ؼ�) ���� ������ �Ѿ
	if (_pos.y > GWinSizeY * 1.5 || _pos.y < -GWinSizeY * 1.5) {	// ��Ÿ����
		FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

		if (scene) {
			scene->ChangePlayerTurn();
		}

		GET_SINGLE(ObjectManager)->Remove(this);	// Bullet ��ü ����
		return;
	}
}

// 82. Bullet::Render(HDC hdc) ����
void Bullet::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, static_cast<int32>(_radius));
}
