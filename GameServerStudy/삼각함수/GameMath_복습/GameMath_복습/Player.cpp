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

// 26. Player::Update() 구현 + Init()
// 71. Player::Update() 수정
void Player::Update()
{
	// 프레임 간의 시간 간격을 얻어 움직임이 부드럽게 이루어지도록 함
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_playerTurn == false) {
		return;
	}

	// 사용자의 키 입력에 따라 플레이어를 움직임
	// 키가 눌려져 있는 경우에만 플레이어의 위치 업데이트
	// 누르고 있는동안 계속 true여야 함. (계속 누르고 있는 경우)
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A)) {
		_pos.x -= _stat.speed * deltaTime;
		_dir = Dir::Left;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D)) {
		_pos.x += _stat.speed * deltaTime;
		_dir = Dir::Right;
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar)) {
		// TODO: 미사일 발사
	}
}

// 33. Player::Render() 구현
// 74. Player::Render(HDC hdc) 수정
void Player::Render(HDC hdc)
{
	if (_dir == Dir::Left) {	// 왼쪽 이동 시
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh) {
			mesh->Render(hdc, _pos);
		}
	}
	else {						// 오른쪽 이동 시
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh) {
			mesh->Render(hdc, _pos);
		}
	}
}

// 68. 구현 필요 (순서 조정필요)
wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank) {
		return L"MissileTank";
	}
	return L"CanonTank";
}