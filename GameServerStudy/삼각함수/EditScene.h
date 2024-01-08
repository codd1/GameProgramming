#pragma once
#include "Scene.h"

// ��ǥ�� �ϳ��� �� �׸��� �׸� ������ �� ��ǥ �״�� ���Ϸ� �����ϱ� ���� Ŭ����
class EditScene : public Scene
{
public:
	EditScene();
	virtual ~EditScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	// pair�� ����? ���̱� ������. (��𼭺��� ������)
	vector<pair<POINT, POINT>> _lines;

	bool _isFirst = true;		// ó�� �����? = lastPos�� �ִ���?
	POINT _lastPos = {};	// ������ ���� ��ǥ
};

