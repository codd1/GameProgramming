#include "pch.h"
#include "Player.h"
#include "InputManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();
}

void Player::Tick()
{
	Super::Tick();

	// 넣고 싶은 기능이 있다면 여기에 구현 (TODO)
	if(GET_SINGLE(InputManager)->GetButton(KeyType::W)) {
		
	}
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}
