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

// 28. Monster::Update() 구현 + Init()
void Monster::Update()
{

}

// 34. Monster::Render() 구현
void Monster::Render(HDC hdc)
{
	// 56. 삼각형을 그리고, 그 삼각형 안에 마우스가 있는지 확인하는 것을 구현하고자 함.
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

	// pt1 좌표에서 시작하는 벡터 외적
	Utils::DrawLine(hdc, _pt1, mousePos);

	Vector v12 = _pt2 - _pt1;		// v1 -> v2 방향 벡터
	Vector v1m = mousePos - _pt1;	// mousePos -> _pt1 방향 벡터
	Vector v13 = _pt3 - _pt1;		// v1 -> v3 방향 벡터
	
	float c1 = v12.Cross(v1m);	// v12 x v1m (외적)
	float c2 = v1m.Cross(v13);	// v1m x v13 (외적)		+) 외적은 교환법칙 불가

	// pt2 좌표에서 시작하는 벡터 외적
	Utils::DrawLine(hdc, _pt2, mousePos);

	Vector v21 = _pt1 - _pt2;		// v2 -> v1 방향 벡터
	Vector v2m = mousePos - _pt2;	// mousePos -> _pt2 방향 벡터
	Vector v23 = _pt3 - _pt2;		// v2 -> v3 방향 벡터

	float c3 = v21.Cross(v2m);	// v21 x v2m (외적)
	float c4 = v2m.Cross(v23);	// v2m x v23 (외적)

	// pt3 좌표에서 시작하는 벡터 외적
	Utils::DrawLine(hdc, _pt3, mousePos);

	Vector v31 = _pt1 - _pt3;		// v3 -> v1 방향 벡터
	Vector v3m = mousePos - _pt3;	// mousePos -> _pt3 방향 벡터
	Vector v32 = _pt2 - _pt3;		// v3 -> v2 방향 벡터

	float c5 = v31.Cross(v3m);	// v31 x v3m (외적)
	float c6 = v3m.Cross(v32);	// v3m x v32 (외적)

	if ((c1*c2>=0) && (c3*c4>=0) && (c5*c6>=0)) {
		// 각 외적끼리 부호가 같은 경우 = mousePos가 범위 내에 있는 경우
		Utils::DrawTextW(hdc, { 20, 130 }, L"마우스 좌표가 범위 내에 있습니다!");
	}
	else {
		// mousePos가 범위 내에 없는 경우
		HBRUSH hBrush = ::CreateSolidBrush(RGB(255, 255, 255)); // 흰색으로 설정
		FillRect(hdc, &rect, hBrush);
		DeleteObject(hBrush);
	}

	wstring str1 = format(L"c1({0}), c2({1})", c1, c2);
	Utils::DrawTextW(hdc, { 20,50 }, str1);

	wstring str2 = format(L"c3({0}), c4({1})", c3, c4);
	Utils::DrawTextW(hdc, { 20,70 }, str2);

	wstring str3 = format(L"c5({0}), c6({1})", c5, c6);
	Utils::DrawTextW(hdc, { 20,90 }, str3);
}
