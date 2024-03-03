#pragma once

// 8. Scene 클래스 생성
// DevScene, GameScene, EditScene을 만들기 전, 최상위객체를 만듦
// 따라서 Scene 클래스는 싱글톤으로 동작하면 X
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;
};

