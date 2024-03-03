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

// 26. Player::Update() 구현 + Init()
// 71. Player::Update() 수정
void Player::Update()
{
	// 프레임 간의 시간 간격을 얻어 움직임이 부드럽게 이루어지도록 함
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_playerTurn == false) {
		return;
	}

	// 86. 함수 추가/구현
	UpdateFireAngle();

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

	// 85. W, S키를 통해 미사일 각도 설정
	if (GET_SINGLE(InputManager)->GetButton(KeyType::W)) {
		_fireAngle = ::clamp(_fireAngle + 50 * deltaTime, 0.f, 75.f);	// 0도 ~ 75도 사이로 각도 제한
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S)) {
		_fireAngle = ::clamp(_fireAngle - 50 * deltaTime, 0.f, 75.f);	// 0도 ~ 75도 사이로 각도 제한
	}

	// 83. 미사일 발사 힘 게이지 세팅 (게이지가 높을수록 발사 속도가 빨라짐)
	if (GET_SINGLE(InputManager)->GetButton(KeyType::SpaceBar)) {	// 오타수정: GetButtonDown -> GetButton
		float percent = GET_SINGLE(UIManager)->GetPowerPercent();	// default: 0
		percent = min(100, percent + 100 * deltaTime);
		GET_SINGLE(UIManager)->SetPowerPercent(percent);
	}

	// 84. 마우스 떼면 미사일 발사
	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::SpaceBar)) {
		_playerTurn = false;

		float percent = GET_SINGLE(UIManager)->GetPowerPercent();
		float speed = 10.f * percent;	// 게이지에 따라 speed 설정
		float angle = GET_SINGLE(UIManager)->GetBarrelAngle();

		// Bullet 객체 생성 및 기본 세팅
		Bullet* bullet = GET_SINGLE(ObjectManager)->CreateObject<Bullet>();
		bullet->SetPos(_pos);		// Player의 위치에서 Bullet이 나가도록 함.

		// 정규화(빗변 길이 1)가 됐다는 가정하에, cos과 sin으로 x, y 좌표를 구하고 각각 speed를 곱해서 세팅해줌.
		bullet->SetSpeed(Vector{ speed * ::cos(angle * PI / 180), -1 * speed * ::sin(angle * PI / 180) });

		// 90. Owner 세팅
		bullet->SetOwner(this);

		GET_SINGLE(ObjectManager)->Add(bullet);
	}
}

// 33. Player::Render() 구현
// 74. Player::Render(HDC hdc) 수정
// 76. LineMesh 클래스의 매개변수 추가로, Player::Render도 매개변수 추가
void Player::Render(HDC hdc)
{
	if (_dir == Dir::Left) {	// 왼쪽 이동 시
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh) {
			mesh->Render(hdc, _pos, 0.5f, 0.5f);	// UI 0.5배
		}
	}
	else {						// 오른쪽 이동 시
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh) {
			mesh->Render(hdc, _pos, -0.5f, 0.5f);	// <- 방향으로 이동 = x좌표 (-) + UI 0.5배
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

void Player::UpdateFireAngle()
{
	if (_dir == Dir::Left) {	// 왼쪽을 바라보는 경우
		GET_SINGLE(UIManager)->SetPlayerAngle(180);
		GET_SINGLE(UIManager)->SetBarrelAngle(180 - _fireAngle);
	}
	else {						// 오른쪽을 바라보는 경우
		GET_SINGLE(UIManager)->SetPlayerAngle(0);
		GET_SINGLE(UIManager)->SetBarrelAngle(_fireAngle);
	}
}
