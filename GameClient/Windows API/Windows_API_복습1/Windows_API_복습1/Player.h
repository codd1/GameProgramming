#pragma once
#include "Object.h"

// 13~14. Player, Monster 클래스 생성
class Player : public Object
{
public:
	Player();
	virtual ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

