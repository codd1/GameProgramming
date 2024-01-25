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

// 28. Monster::Update() ���� + Init()
void Monster::Update()
{
	// 52. �� ���콺 ��ġ�� ���� ���� �� ���� ����� ������ ���Ͱ� �̵��ϵ��� ���� ����
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();

	// ���Ϸ��� ��: ���Ͱ� �̵��� ��ġ (���� �̿�) = x
	
	// ���Ͱ� ������ �� �ִ� ������ ���������� ���������� ����
	Vector v1 = _end - _start;
	// ���Ͱ� ������ �� �ִ� ������ ���������� ���콺 ��ġ������ ����
	Vector v2 = mousePos - _start;

	float maxLength = v1.Length();	// ���Ͱ� ������ �� �ִ� ����(��)�� ����

	// v1 �� v2 = |v1||v2|cos�� = |v1||v2|(x/|v2|) = |v1|x
	v1.Normalize();		// x�� ���ϱ� ���ؼ� |v1|�� ũ�⸦ 1�� �����. (����ȭ)
	float dot = v1.Dot(v2);		// ����(= v1 �� v2)�� ����ϸ� ���Ϸ��� �� x�� ���´�.

	Pos pos = _start + v1 * dot;	// �������� v1*dot(����+�Ÿ�)�� ���Ѵ�.

	if (dot < 0 || dot > maxLength) {
		return;
	}

	_pos = pos;		// ������ ��ġ�� ����� ��ġ�� �ű��.
}

// 34. Monster::Render() ����
void Monster::Render(HDC hdc)
{
	//Utils::DrawRect(hdc, _pos, 50, 50);

	// 53. ���Ͱ� ������ �� �ִ� ����(��)�� ����(��)�� �׷��ش�.
	Utils::DrawCircle(hdc, _pos, 50);

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);
	{
		Utils::DrawLine(hdc, _start, _end);
	}
	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}
