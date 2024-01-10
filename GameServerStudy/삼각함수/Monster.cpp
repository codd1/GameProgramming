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

}

void Monster::Render(HDC hdc)
{
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);
	{
		Utils::DrawLine(hdc, _pt1, _pt2);
		Utils::DrawLine(hdc, _pt2, _pt3);
		Utils::DrawLine(hdc, _pt3, _pt1);
	}
	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);

	Utils::DrawLine(hdc, _pt1, mousePos);

	Vector v12 = _pt2 - _pt1;		// v12 벡터 (v1 -> v2)
	Vector v1m = mousePos - _pt1;	// v1m 벡터 (v1 -> vm)
	Vector v13 = _pt3 - _pt1;		// v13 벡터 (v1 -> v3)

	// 정규화는 필수 X
	v12.Normalize();
	v1m.Normalize();
	v13.Normalize();

	float c1 = v12.Cross(v1m);		// v12 x v1m (외적)
	float c2 = v1m.Cross(v13);		// v1m x v13 (외적)

	if (c1 >= 0 && c2 >= 0) {
		// 둘 다 양수일 경우 부호가 같은 경우이므로 mousePos가 범위 내에 있는 경우
	}
	else {
		// mousePos가 범위 내에 없는 경우
	}

	wstring str = std::format(L"c1({0}), c2({1})", c1, c2);
	Utils::DrawTextW(hdc, { 20, 50 }, str);
}
