#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "EditScene.h"
#include "GameScene.h"

void SceneManager::Init()
{
}

void SceneManager::Update()
{
}

void SceneManager::Render(HDC hdc)
{
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType) {
		// �ٲٷ��� Scene�� ���� Scene�� ��� �״�� ����
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
	case SceneType::EditScene:
		newScene = new EditScene();
		break;
	}

	// ������ scene �޸� ���� (nullptr�� ��� ���������� ��ŵ)
	SAFE_DELETE(_scene);

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
