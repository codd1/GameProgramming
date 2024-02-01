#pragma once
class Scene;

// 7. SceneManager ����
class SceneManager
{
public:
	DECLARE_SINGLE(SceneManager);

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	// 42. Clear() �Լ� ����
	void Clear();

	void ChangeScene(SceneType sceneType);

private:
	// Scene Ŭ������ �����͸� ����Ű�� ������ ����(��� ����)
	// Scene Ŭ������ ���ǵǾ� ���� �ʾƵ� ��� ���� --> ����!!!
	Scene* _scene;
	SceneType _sceneType = SceneType::None;

public:
	// 82. �ʿ��� �޼��� �߰�
	Scene* GetCurrentScene() { return _scene; }
};

