#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"

#include "ObjectManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"

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
		//_pos.y -= _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S)) {
		//_pos.y += _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q)) {
		
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::E)) {
		
	}


	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar)) {
		// TODO: 미사일 발사
		
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
	

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));		// 빨간색 펜
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	//Utils::DrawLine(hdc, _pos, GetFirePos());

	::SelectObject(hdc, oldPen);		// 잠시 빨간펜으로 그려주고 다시 원래 펜으로 복원해줌
	::DeleteObject(pen);
}

wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank) {
		return L"MissileTank";
	}
	return L"CanonTank";
}
