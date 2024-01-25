#pragma once
#include "Object.h"

// 13~14. Player, Monster Ŭ���� ����
class Monster : public Object
{
public:
	Monster();
	virtual ~Monster() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	// ���Ͱ� ������ �� �ִ� ����(��)
	Vector _start = { 300, 300 };
	Vector _end = { 600,250 };
};

