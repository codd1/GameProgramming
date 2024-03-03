#pragma once

class Scene;

// ���� ���� ��ü�� SceneManager�� ����
// ���� ���� �����ϰ� �ִ� ���� ������Ʈ �ϱ� ����
class SceneManager
{
	DECLARE_SINGLE(SceneManager)

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	
	void Clear();
public:
	void ChangeScene(SceneType sceneType);

	Scene* GetCurrentScene() { return _scene; }
private:
	Scene* _scene;
	SceneType _sceneType = SceneType::None;
};

