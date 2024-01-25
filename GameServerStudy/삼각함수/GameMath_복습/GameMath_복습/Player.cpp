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
void Player::Update()
{
	// ������ ���� �ð� ������ ��� �������� �ε巴�� �̷�������� ��
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// ������� Ű �Է¿� ���� �÷��̾ ������
	// Ű�� ������ �ִ� ��쿡�� �÷��̾��� ��ġ ������Ʈ
	// ������ �ִµ��� ��� true���� ��. (��� ������ �ִ� ���)
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A)) {
		_pos.x -= _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W)) {
		_pos.y -= _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S)) {
		_pos.y += _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D)) {
		_pos.x += _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar)) {
		// 37. �̻��� �浹 �� �̻��� �߻� ����
		Missile* missile = GET_SINGLE(ObjectManager)->CreateObject<Missile>();
		missile->SetPos(_pos);
		GET_SINGLE(ObjectManager)->Add(missile);
		// �����ؼ� �߻�Ǵ��� Ȯ��
	}
}

// 33. Player::Render() ����
void Player::Render(HDC hdc)
{
	//Utils::DrawCircle(hdc, _pos, 50);		// Player �����̴��� Ȯ�ο� (Update() �κ�)
	
	// ResourceBase, LineMesh Ŭ���� ����
	const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(L"Player");
	if (mesh) {
		mesh->Render(hdc, _pos);
	}

	// Ȯ���� ���� ���� Player.txt ������ ������ش�.
	// --> ������ Unit.txt�� �����ؼ� �̸��� �ٲ㼭 ���ڴ�.
}
