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
		player->SetPos(Pos{ 400, 400 });
		GET_SINGLE(ObjectManager)->Add(player);
	}

	// Monster 5마리
	for (int32 i = 0; i < 5; i++)
	{
		Monster* monster = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
		monster->SetPos(Pos{ static_cast<float>(i + 1) * 100, 100 });
		GET_SINGLE(ObjectManager)->Add(monster);
	}
}

void GameScene::Update()
{
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	// 미사일을 쏘면 여기서 에러가 발생하는데,
	// 벡터를 순회함과 동시에 벡터에 강제적으로 Add 해주고 있어서 문제가 되는 것이다.
	for (Object* object : objects) {
		object->Update();
	}
}

void GameScene::Render(HDC hdc)
{
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects) {
		object->Render(hdc);
	}
}
