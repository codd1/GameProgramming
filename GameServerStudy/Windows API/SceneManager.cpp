#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "GameScene.h"

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	if (_scene) {
		_scene->Update();
	}
}

void SceneManager::Render(HDC hdc)
{
	if (_scene) {
		_scene->Render(hdc);
	}
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType) {		// 바꾸려는 Scene이 현재 Scene인 경우
		return;
	}

	Scene* newScene = nullptr;

	switch (sceneType) {
	case SceneType::DevScene:
		newScene = new DevScene();
		break;
	case SceneType::GameScene:
		newScene = new GameScene();
		break;
	}
	
	SAFE_DELETE(_scene);
	/*if (_scene) {
		delete _scene;
		_scene = nullptr;
	}*/

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
