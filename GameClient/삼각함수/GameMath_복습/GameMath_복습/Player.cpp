#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "LineMesh.h"
#include "ResourceManager.h"
#include "Missile.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "Bullet.h"

Player::Player() : Object(ObjectType::Player)
{
}

Player::~Player()
{
}

void Player::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;
}

// 26. Player::Update() ���� + Init()
// 71. Player::Update() ����
void Player::Update()
{
	// ������ ���� �ð� ������ ��� �������� �ε巴�� �̷�������� ��
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_playerTurn == false) {
		return;
	}

	// 86. �Լ� �߰�/����
	UpdateFireAngle();

	// ������� Ű �Է¿� ���� �÷��̾ ������
	// Ű�� ������ �ִ� ��쿡�� �÷��̾��� ��ġ ������Ʈ
	// ������ �ִµ��� ��� true���� ��. (��� ������ �ִ� ���)
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A)) {
		_pos.x -= _stat.speed * deltaTime;
		_dir = Dir::Left;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D)) {
		_pos.x += _stat.speed * deltaTime;
		_dir = Dir::Right;
	}

	// 85. W, SŰ�� ���� �̻��� ���� ����
	if (GET_SINGLE(InputManager)->GetButton(KeyType::W)) {
		_fireAngle = ::clamp(_fireAngle + 50 * deltaTime, 0.f, 75.f);	// 0�� ~ 75�� ���̷� ���� ����
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S)) {
		_fireAngle = ::clamp(_fireAngle - 50 * deltaTime, 0.f, 75.f);	// 0�� ~ 75�� ���̷� ���� ����
	}

	// 83. �̻��� �߻� �� ������ ���� (�������� �������� �߻� �ӵ��� ������)
	if (GET_SINGLE(InputManager)->GetButton(KeyType::SpaceBar)) {	// ��Ÿ����: GetButtonDown -> GetButton
		float percent = GET_SINGLE(UIManager)->GetPowerPercent();	// default: 0
		percent = min(100, percent + 100 * deltaTime);
		GET_SINGLE(UIManager)->SetPowerPercent(percent);
	}

	// 84. ���콺 ���� �̻��� �߻�
	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::SpaceBar)) {
		_playerTurn = false;

		float percent = GET_SINGLE(UIManager)->GetPowerPercent();
		float speed = 10.f * percent;	// �������� ���� speed ����
		float angle = GET_SINGLE(UIManager)->GetBarrelAngle();

		// Bullet ��ü ���� �� �⺻ ����
		Bullet* bullet = GET_SINGLE(ObjectManager)->CreateObject<Bullet>();
		bullet->SetPos(_pos);		// Player�� ��ġ���� Bullet�� �������� ��.

		// ����ȭ(���� ���� 1)�� �ƴٴ� �����Ͽ�, cos�� sin���� x, y ��ǥ�� ���ϰ� ���� speed�� ���ؼ� ��������.
		bullet->SetSpeed(Vector{ speed * ::cos(angle * PI / 180), -1 * speed * ::sin(angle * PI / 180) });

		// 90. Owner ����
		bullet->SetOwner(this);

		GET_SINGLE(ObjectManager)->Add(bullet);
	}
}

// 33. Player::Render() ����
// 74. Player::Render(HDC hdc) ����
// 76. LineMesh Ŭ������ �Ű����� �߰���, Player::Render�� �Ű����� �߰�
void Player::Render(HDC hdc)
{
	if (_dir == Dir::Left) {	// ���� �̵� ��
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh) {
			mesh->Render(hdc, _pos, 0.5f, 0.5f);	// UI 0.5��
		}
	}
	else {						// ������ �̵� ��
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh) {
			mesh->Render(hdc, _pos, -0.5f, 0.5f);	// <- �������� �̵� = x��ǥ (-) + UI 0.5��
		}
	}
}

// 68. ���� �ʿ� (���� �����ʿ�)
wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank) {
		return L"MissileTank";
	}
	return L"CanonTank";
}

void Player::UpdateFireAngle()
{
	if (_dir == Dir::Left) {	// ������ �ٶ󺸴� ���
		GET_SINGLE(UIManager)->SetPlayerAngle(180);
		GET_SINGLE(UIManager)->SetBarrelAngle(180 - _fireAngle);
	}
	else {						// �������� �ٶ󺸴� ���
		GET_SINGLE(UIManager)->SetPlayerAngle(0);
		GET_SINGLE(UIManager)->SetBarrelAngle(_fireAngle);
	}
}
