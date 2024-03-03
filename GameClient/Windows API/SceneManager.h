#pragma once

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

private:
	class Scene* _scene;
	SceneType _sceneType = SceneType::None;
};

