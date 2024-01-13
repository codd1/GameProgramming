#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"

#include "ObjectManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"
#include "UiManager.h"
#include "Bullet.h"

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

	if (_playerTurn == false) {
		return;
	}

	UpdateFireAngle();

	// 누르고 있는 동안 계속 True여야 함. (계속 누르고 있는 경우)
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A)) {
		_pos.x -= _stat.speed * deltaTime;
		_dir = Dir::Left;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D)) {
		_pos.x += _stat.speed * deltaTime;
		_dir = Dir::Right;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W)) {
		_fireAngle = ::clamp(_fireAngle + 50 * deltaTime, 0.f, 75.f);	// 0도 ~ 75도 사이
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S)) {
		_fireAngle = ::clamp(_fireAngle - 50 * deltaTime, 0.f, 75.f);	// 0도 ~ 75도 사이
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q)) {
		
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::E)) {
		
	}


	if (GET_SINGLE(InputManager)->GetButton(KeyType::SpaceBar)) {
		// TODO: 미사일 발사
		float percent = GET_SINGLE(UIManager)->GetPowerPercent();
		percent = min(100, percent + 100 * deltaTime);
		GET_SINGLE(UIManager)->SetPowerPercent(percent);
	}

	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::SpaceBar)) {
		// 슈팅
		_playerTurn = false;	// 슈팅하면 차례 전환

		float percent = GET_SINGLE(UIManager)->GetPowerPercent();
		float speed = 10.f * percent;
		float angle = GET_SINGLE(UIManager)->GetBarrelAngle();

		// TODO
		Bullet* bullet = GET_SINGLE(ObjectManager)->CreateObject<Bullet>();
		bullet->SetOwner(this);
		bullet->SetPos(_pos);
		bullet->SetSpeed(Vector{ speed * ::cos(angle * PI / 180), -1 * speed * ::sin(angle * PI / 180) });
		GET_SINGLE(ObjectManager)->Add(bullet);
	}
}

void Player::Render(HDC hdc)
{
	if (_dir == Dir::Left) {	// 왼쪽으로 이동 시
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh) {
			mesh->Render(hdc, _pos, 0.5f, 0.5f);
		}
	}
	else {		// 오른쪽 이동 시
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh) {
			mesh->Render(hdc, _pos, -0.5f, 0.5f);		// 부호 바꾸면 좌우반전
		}
	}

	if (_playerTurn) {
		RECT rect;
		rect.bottom = static_cast<LONG>(_pos.y - 60);
		rect.left = static_cast<LONG>(_pos.x - 10);
		rect.right = static_cast<LONG>(_pos.x + 10);
		rect.top = static_cast<LONG>(_pos.y - 80);

		HBRUSH brush = ::CreateSolidBrush(RGB(250, 236, 197));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

		::Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

		::SelectObject(hdc, oldBrush);
		::DeleteObject(brush);
	}

	
}

wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank) {
		return L"MissileTank";
	}
	return L"CanonTank";
}

void Player::UpdateFireAngle()
{
	if (_dir == Dir::Left) {	// 왼쪽을 보고 있는 경우
		GET_SINGLE(UIManager)->SetPlayerAngle(180);
		GET_SINGLE(UIManager)->SetBarrelAngle(180 - _fireAngle);
	}
	else {
		GET_SINGLE(UIManager)->SetPlayerAngle(0);
		GET_SINGLE(UIManager)->SetBarrelAngle(_fireAngle);
	}
}
