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

// 28. Monster::Update() ���� + Init()
void Monster::Update()
{

}

// 34. Monster::Render() ����
void Monster::Render(HDC hdc)
{
	// 56. ���� - �ﰢ���� �׸���, �� �ﰢ�� �ȿ� ���콺�� �ִ��� Ȯ���ϴ� ���� �����ϰ��� ��.
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();

	// 57. ���ﰢ�Լ� - ���Ͱ� �ٶ󺸴� ����� ���Ͱ� ���콺 Ŀ���� �ٶ󺸴� ���� ������ ���� ���ϱ�
	Utils::DrawCircle(hdc, _pos, 100);

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);
	{
		// ���Ͱ� �ٶ󺸴� ���� (v1)
		Utils::DrawLine(hdc, _pos, _lookPos);
	}
	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);

	Vector monsterToMouseDir = mousePos - _pos;		// ���Ͱ� ���콺 Ŀ���� �ٶ󺸴� ����(v2)
	monsterToMouseDir.Normalize();

	Vector dir = _lookDir;
	dir.Normalize();

	float dot = monsterToMouseDir.Dot(_lookDir);
	float radian = ::acos(dot);		// ��ũ�ڻ���(���ﰢ�Լ�)
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
