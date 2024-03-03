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
	// 54. 몬스터 1개로
	Monster* monster = GET_SINGLE(ObjectManager)->CreateObject<Monster>();
	GET_SINGLE(ObjectManager)->Add(monster);
}

// 25. GameScene::Update() 구현 (DevScene, EditScene 구현, 확인 후 GameScene)
void GameScene::Update()
{
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();

	for (Object* object : objects) {
		object->Update();
	}
}

// 29. GameScene::Render() 구현
void GameScene::Render(HDC hdc)
{
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects) {
		object->Render(hdc);
	}
}
