#include "pch.h"
#include "Monster.h"
#include "InputManager.h"

Monster::Monster() : Object(ObjectType::Monster)
{
}

Monster::~Monster()
{
}

void Monster::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 10;
}

void Monster::Update()
{
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();

	// start -> end
	Vector v1 = _end - _start;

	// start -> mousePos
	Vector v2 = mousePos - _start;

	float maxLength = v1.Length();

	v1.Normalize();					// v1을 단위벡터로 만들고
	float dot = v1.Dot(v2);			// v1과 v2를 내적한다.
	Pos pos = _start + v1 * dot;	// 몬스터 이동 경로에 v1*내적 값을 더하면 마우스 좌표에 따라 몬스터 좌표가 바뀌게 된다.

	if (dot < 0 || dot > maxLength) {
		return;
	}

	_pos = pos;
}

void Monster::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 50);

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);
	{
		Utils::DrawLine(hdc, _start, _end);
	}
	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}
