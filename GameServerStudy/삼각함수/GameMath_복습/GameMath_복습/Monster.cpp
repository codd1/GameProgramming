#include "pch.h"
#include "Monster.h"

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
	// 만들 게임은 몬스터가 가만히 있는 것이므로 따로 구현할 내용 X
	// TODO: 몬스터 업데이트가 필요하면 추가
}

// 34. Monster::Render() 구현
void Monster::Render(HDC hdc)
{
	Utils::DrawRect(hdc, _pos, 50, 50);
}
