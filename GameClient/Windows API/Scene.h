#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene();

	// �ֻ��� ��ü�μ��� ���Ҹ� �ϹǷ� ���������Լ��� �����.
	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

protected:

};

