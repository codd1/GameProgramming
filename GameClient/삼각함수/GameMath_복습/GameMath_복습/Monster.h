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
	Vector _lookPos = {};	// 몬스터가 바라보는 좌표
	Vector _lookDir = {};

	RECT rect = { 20, 130, 100, 170 };
};

