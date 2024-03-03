#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene();

	// 최상위 객체로서의 역할만 하므로 순수가상함수로 만든다.
	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

protected:

};

