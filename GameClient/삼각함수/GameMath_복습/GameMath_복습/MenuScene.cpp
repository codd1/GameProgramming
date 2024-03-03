#include "pch.h"
#include "MenuScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "LineMesh.h"
#include "ResourceManager.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Init()
{
}

// 65. MenuScene::Update() 구현
void MenuScene::Update()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E)) {
		GET_SINGLE(SceneManager)->ChangeScene(SceneType::FortressScene);
	}
}

// 72. MenuScene::Render(HDC hdc) 구현
void MenuScene::Render(HDC hdc)
{
	const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(L"Menu");
	if (mesh) {
		mesh->Render(hdc, Pos{ 0,0 });
	}
}
