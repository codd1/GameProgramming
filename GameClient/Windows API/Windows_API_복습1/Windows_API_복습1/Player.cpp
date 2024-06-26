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
void Player::Update()
{
	// 프레임 간의 시간 간격을 얻어 움직임이 부드럽게 이루어지도록 함
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 사용자의 키 입력에 따라 플레이어를 움직임
	// 키가 눌려져 있는 경우에만 플레이어의 위치 업데이트
	// 누르고 있는동안 계속 true여야 함. (계속 누르고 있는 경우)
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
		// 37. 미사일 충돌 전 미사일 발사 구현
		Missile* missile = GET_SINGLE(ObjectManager)->CreateObject<Missile>();
		missile->SetPos(_pos);
		GET_SINGLE(ObjectManager)->Add(missile);
		// 실행해서 발사되는지 확인
	}
}

// 33. Player::Render() 구현
void Player::Render(HDC hdc)
{
	//Utils::DrawCircle(hdc, _pos, 50);		// Player 움직이는지 확인용 (Update() 부분)
	
	// ResourceBase, LineMesh 클래스 생성
	const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(L"Player");
	if (mesh) {
		mesh->Render(hdc, _pos);
	}

	// 확인을 위해 따로 Player.txt 파일을 만들어준다.
	// --> 지금은 Unit.txt를 복사해서 이름만 바꿔서 쓰겠다.
}
