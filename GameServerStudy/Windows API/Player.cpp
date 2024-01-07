#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
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
	// 데이터시트: 아이템 정보(속성) 등 (Excel, Json 등으로 만듦)
	// 데이터베이스: 유저 정보 등 (Oracle, MySQL 등으로 만듦)
	
	// TODO: Data
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;
}

void Player::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 누르고 있는 동안 계속 True여야 함. (계속 누르고 있는 경우)
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A)) {
		_pos.x -= _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D)) {
		_pos.x += _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W)) {
		_pos.y -= _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S)) {
		_pos.y += _stat.speed * deltaTime;
	}


	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar)) {
		// TODO: 미사일 발사
		Missile* missile = GET_SINGLE(ObjectManager)->CreateObject<Missile>();
		missile->SetPos(_pos);
		GET_SINGLE(ObjectManager)->Add(missile);
	}
}

void Player::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 50);
}
