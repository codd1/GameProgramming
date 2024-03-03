#include "pch.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "EditScene.h"
//#include "GameScene.h"	// �ּ�ó�� �� �ϸ� ��Ŀ ���� �߻�

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	if (_scene) {
		_scene->Update();	// DevScene, EditScene, GameScene
	}
}

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
		// �ٲٷ��� Scene�� ���� Scene�� ��� �״�� ����
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
	}

	// ������ scene �޸� ���� (nullptr�� ��� ���������� ��ŵ)
	SAFE_DELETE(_scene);

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
