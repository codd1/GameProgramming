#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "EditScene.h"
//#include "GameScene.h"	// 주석처리 안 하면 링커 오류 발생
#include "MenuScene.h"
#include "FortressScene.h"

void SceneManager::Init()
{
}

// 18. SceneManager::Update() 구현
void SceneManager::Update()
{
	if (_scene) {
		_scene->Update();	// DevScene, EditScene, GameScene
	}
}

// 22. SceneManager::Render 구현
void SceneManager::Render(HDC hdc)
{
	if (_scene) {
		_scene->Render(hdc);	// DevScene, EditScene, GameScene
	}
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType) {
		// 바꾸려는 Scene이 현재 Scene인 경우 그대로 리턴
		return;
	}

	Scene* newScene = nullptr;

	switch (sceneType) {
	case SceneType::DevScene:
		newScene = new DevScene();
		break;
	case SceneType::EditScene:
		newScene = new EditScene();
		break;
	// 62. case 추가
	case SceneType::MenuScene:
		newScene = new MenuScene();
		break;
	case SceneType::FortressScene:
		newScene = new FortressScene();
		break;
	}

	// 기존의 scene 메모리 해제 (nullptr인 경우 내부적으로 스킵)
	SAFE_DELETE(_scene);

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
