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
	// 52. 내 마우스 위치에 따라 범위 내 가장 가까운 곳으로 몬스터가 이동하도록 구현 예정
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();

	// 구하려는 값: 몬스터가 이동할 위치 (내적 이용) = x
	
	// 몬스터가 움직일 수 있는 범위의 시작점에서 끝점까지의 벡터
	Vector v1 = _end - _start;
	// 몬스터가 움직일 수 있는 범위의 시작점에서 마우스 위치까지의 벡터
	Vector v2 = mousePos - _start;

	float maxLength = v1.Length();	// 몬스터가 움직일 수 있는 범위(선)의 길이

	// v1 · v2 = |v1||v2|cosθ = |v1||v2|(x/|v2|) = |v1|x
	v1.Normalize();		// x를 구하기 위해서 |v1|의 크기를 1로 만든다. (정규화)
	float dot = v1.Dot(v2);		// 내적(= v1 · v2)을 계산하면 구하려는 값 x가 나온다.

	Pos pos = _start + v1 * dot;	// 시작점에 v1*dot(방향+거리)을 더한다.

	if (dot < 0 || dot > maxLength) {
		return;
	}

	_pos = pos;		// 몬스터의 위치를 계산한 위치로 옮긴다.
}

// 34. Monster::Render() 구현
void Monster::Render(HDC hdc)
{
	//Utils::DrawRect(hdc, _pos, 50, 50);

	// 53. 몬스터가 움직일 수 있는 범위(선)과 몬스터(원)를 그려준다.
	Utils::DrawCircle(hdc, _pos, 50);

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);
	{
		Utils::DrawLine(hdc, _start, _end);
	}
	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}
