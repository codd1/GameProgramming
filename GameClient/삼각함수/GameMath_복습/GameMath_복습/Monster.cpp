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

	_pos = { 400, 400 };

	_lookPos = Pos{ 550,70 };
	_lookDir = _lookPos - _pos;
	_lookDir.Normalize();
}

// 28. Monster::Update() 구현 + Init()
void Monster::Update()
{

}

// 34. Monster::Render() 구현
void Monster::Render(HDC hdc)
{
	// 56. 외적 - 삼각형을 그리고, 그 삼각형 안에 마우스가 있는지 확인하는 것을 구현하고자 함.
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();

	// 57. 역삼각함수 - 몬스터가 바라보는 방향과 몬스터가 마우스 커서를 바라보는 방향 사이의 각도 구하기
	Utils::DrawCircle(hdc, _pos, 100);

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);
	{
		// 몬스터가 바라보는 벡터 (v1)
		Utils::DrawLine(hdc, _pos, _lookPos);
	}
	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);

	Vector monsterToMouseDir = mousePos - _pos;		// 몬스터가 마우스 커서를 바라보는 벡터(v2)
	monsterToMouseDir.Normalize();

	Vector dir = _lookDir;
	dir.Normalize();

	float dot = monsterToMouseDir.Dot(_lookDir);
	float radian = ::acos(dot);		// 아크코사인(역삼각함수)
	float angle = radian * 180 / 3.14f;

	float cross = _lookDir.Cross(monsterToMouseDir);
	if (cross < 0) {
		angle = 360 - angle;
	}

	{
		wstring str1 = format(L"Angle({0})", angle);
		Utils::DrawTextW(hdc, { 20,50 }, str1);
	}
}
