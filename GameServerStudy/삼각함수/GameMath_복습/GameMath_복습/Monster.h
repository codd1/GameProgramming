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
	// 몬스터가 움직일 수 있는 범위(선)
	Vector _start = { 300, 300 };
	Vector _end = { 600,250 };
};

