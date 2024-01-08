#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Missile.h"
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

	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q)) {
		_barrelAngle += 10 * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::E)) {
		_barrelAngle -= 10 * deltaTime;
	}


	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar)) {
		// TODO: 미사일 발사
		Missile* missile = GET_SINGLE(ObjectManager)->CreateObject<Missile>();
		missile->SetPos(GetFirePos());		// 이제 비행기 몸통이 아니라 포신의 좌표에서 미사일이 나가게 된다.
		missile->SetAngle(_barrelAngle);	// 포신의 각도로 미사일 각도 세팅
		GET_SINGLE(ObjectManager)->Add(missile);
	}
}

void Player::Render(HDC hdc)
{
	const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(L"Player");
	if (mesh) {
		mesh->Render(hdc, _pos);
	}

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));		// 빨간색 펜
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	Utils::DrawLine(hdc, _pos, GetFirePos());

	::SelectObject(hdc, oldPen);		// 잠시 빨간펜으로 그려주고 다시 원래 펜으로 복원해줌
	::DeleteObject(pen);
}

Pos Player::GetFirePos()
{
	Pos firePos = _pos;

	/*   /|			( 삼각함수 )
		/ |
	   /__|
	   여기서 _barrelLength는 대각선 부분을 의미
	   그러므로 밑변을 구하려면 _barrelLength * cos θ
			   높이를 구하려면 _barrelLength * sin θ		*/
	firePos.x += _barrelLength * ::cos(_barrelAngle);
	firePos.y -= _barrelLength * ::sin(_barrelAngle);	// Windows API 창에서는 y축이 아래로갈수록 +이므로 -로 계산

	return firePos;
}
