#pragma once

class Scene;

// 게임 세상 자체를 SceneManager가 관리
// 내가 지금 실행하고 있는 씬을 업데이트 하기 위함
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

public:
	Vec2 GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vec2 cameraPos) { _cameraPos = cameraPos; }
private:
	Vec2 _cameraPos = { 400,300 };		// 기준이 되는 카메라 위치
};

