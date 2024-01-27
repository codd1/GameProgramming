#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "FortressScene.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "UIManager.h"

Bullet::Bullet() : Object(ObjectType::Projectile)
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	_radius = 20.f;
}

// 81. Bullet::Update() 구현
void Bullet::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// Wind나 Gravity에 따른 업데이트도 여기서 구현
	// 87. Wind
	float windPercent = GET_SINGLE(UIManager)->GetWindPercent();
	_speed.x += 20 * deltaTime * windPercent;

	// 88. Gravity
	Vector gravity{ 0, 1000 * deltaTime };		// 중력이므로 y에 대한 값만
	_speed += gravity;

	_pos += _speed * deltaTime;


	// 89. 충돌 구현 + _owner 멤버변수 선언
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();

	for (Object* object : objects) {
		if (object->GetObjectType() != ObjectType::Player) {
			continue;
		}

		if (object == _owner) {		// 자기가 쏜 미사일에 맞은 경우
			continue;
		}

		Vector dir = _pos - object->GetPos();	// Player 좌표 -> 미사일 좌표 벡터
		
		// 상대가 맞은 경우
		// Player와 미사일 사이의 거리 < 미사일 반지름 + Player 반지름의 크기
		if (dir.Length() < _radius + object->GetRadius()) {
			FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
			if (scene) {
				scene->ChangePlayerTurn();		// 상대 턴으로 넘어간다.
			}

			GET_SINGLE(ObjectManager)->Remove(this);	// 미사일 객체 삭제
			return;
		}
	}


	// 화면을 크게 넘어갈 경우 (y좌표에 한해서) 다음 턴으로 넘어감
	if (_pos.y > GWinSizeY * 1.5 || _pos.y < -GWinSizeY * 1.5) {	// 오타수정
		FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

		if (scene) {
			scene->ChangePlayerTurn();
		}

		GET_SINGLE(ObjectManager)->Remove(this);	// Bullet 객체 삭제
		return;
	}
}

// 82. Bullet::Render(HDC hdc) 구현
void Bullet::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, static_cast<int32>(_radius));
}
