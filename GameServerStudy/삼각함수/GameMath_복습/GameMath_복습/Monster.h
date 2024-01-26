#pragma once
#include "Object.h"

// 13~14. Player, Monster 클래스 생성
class Monster : public Object
{
public:
	Monster();
	virtual ~Monster() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	Vector _pt1 = { 400,150 };
	Vector _pt2 = { 600,450 };
	Vector _pt3 = { 200,450 };

	RECT rect = { 20, 130, 100, 170 };
};

