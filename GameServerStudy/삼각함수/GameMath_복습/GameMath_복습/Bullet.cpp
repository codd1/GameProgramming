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

// 81. Bullet::Update() ����
void Bullet::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// Wind�� Gravity�� ���� ������Ʈ�� ���⼭ ����

	_pos += _speed * deltaTime;

	// ȭ���� ũ�� �Ѿ ��� (y��ǥ�� ���ؼ�) ���� ������ �Ѿ
	if (_pos.y > GWinSizeX * 1.5 || _pos.y < -GWinSizeY * 1.5) {
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
