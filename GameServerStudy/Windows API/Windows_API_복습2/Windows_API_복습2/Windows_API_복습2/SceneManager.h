#pragma once
// 7. SceneManager ����
class SceneManager
{
public:
	DECLARE_SINGLE(SceneManager);

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void ChangeScene(SceneType sceneType);

private:
	// Scene Ŭ������ �����͸� ����Ű�� ������ ����(��� ����)
	// Scene Ŭ������ ���ǵǾ� ���� �ʾƵ� ��� ���� --> ����!!!
	class Scene* _scene;
	SceneType _sceneType = SceneType::None;
};

