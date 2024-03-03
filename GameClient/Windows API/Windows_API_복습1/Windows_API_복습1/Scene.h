#pragma once

// 8. Scene Ŭ���� ����
// DevScene, GameScene, EditScene�� ����� ��, �ֻ�����ü�� ����
// ���� Scene Ŭ������ �̱������� �����ϸ� X
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;
};

