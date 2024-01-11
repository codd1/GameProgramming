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
	Monster* monster = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
	GET_SINGLE(ObjectManager)->Add(monster);
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
