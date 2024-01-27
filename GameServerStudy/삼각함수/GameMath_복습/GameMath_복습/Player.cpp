#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "LineMesh.h"
#include "ResourceManager.h"
#include "Missile.h"
#include "ObjectManager.h"

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

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar)) {
		// TODO: �̻��� �߻�
	}
}

// 33. Player::Render() ����
// 74. Player::Render(HDC hdc) ����
void Player::Render(HDC hdc)
{
	if (_dir == Dir::Left) {	// ���� �̵� ��
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh) {
			mesh->Render(hdc, _pos);
		}
	}
	else {						// ������ �̵� ��
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh) {
			mesh->Render(hdc, _pos);
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