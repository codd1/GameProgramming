#pragma once
class Scene;

class SceneManager
{
public:
	DECLARE_SINGLE(SceneManager);

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

	void ChangeScene(SceneType sceneType);

private:
	// Scene Ŭ������ �����͸� ����Ű�� ������ ����(��� ����)
	// Scene Ŭ������ ���ǵǾ� ���� �ʾƵ� ��� ���� --> ����!!!
	Scene* _scene;
	SceneType _sceneType = SceneType::None;

public:
	Scene* GetCurrentScene() { return _scene; }
};

