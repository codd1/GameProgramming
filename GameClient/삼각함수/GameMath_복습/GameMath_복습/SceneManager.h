#pragma once
class Scene;

// 7. SceneManager 생성
class SceneManager
{
public:
	DECLARE_SINGLE(SceneManager);

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	// 42. Clear() 함수 구현
	void Clear();

	void ChangeScene(SceneType sceneType);

private:
	// Scene 클래스의 포인터를 가리키는 포인터 변수(멤버 변수)
	// Scene 클래스가 정의되어 있지 않아도 사용 가능 --> 주의!!!
	Scene* _scene;
	SceneType _sceneType = SceneType::None;

public:
	// 82. 필요한 메서드 추가
	Scene* GetCurrentScene() { return _scene; }
};

