#pragma once
#include "Scene.h"

class EditScene : public Scene
{
public:
	EditScene();
	virtual ~EditScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	bool _isFirst = true;	// ���콺�� ó�� ����� Ȯ��
	POINT _lastPos = {};	// ������ ���� ��ǥ
	vector<pair<POINT, POINT>> _lines;		// line�� ���� (line�̱� ������ ���� �׸��� ���� ��ǥ�� ���� ��ǥ�� �ʿ�)
};

