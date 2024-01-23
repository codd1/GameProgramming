#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Monster.h"
#include "ObjectManager.h"
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	// Player
	{
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPos({ 400, 400 });
		GET_SINGLE(ObjectManager)->Add(player);
	}

	// Monster 5¸¶¸®
	for (int32 i = 0; i < 5; i++) {
		Monster* monster = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster->SetPos(Pos{ (static_cast<float>(i + 1)) * 100, 100 });
		GET_SINGLE(ObjectManager)->Add(monster);
	}
}

void GameScene::Update()
{
}

void GameScene::Render(HDC hdc)
{
}
