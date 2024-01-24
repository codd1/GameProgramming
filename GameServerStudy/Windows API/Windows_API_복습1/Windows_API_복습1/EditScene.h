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
	bool _isFirst = true;	// 마우스를 처음 찍는지 확인
	POINT _lastPos = {};	// 이전에 찍은 좌표
	vector<pair<POINT, POINT>> _lines;		// line들 저장 (line이기 때문에 선을 그리는 이전 좌표와 현재 좌표가 필요)
};

